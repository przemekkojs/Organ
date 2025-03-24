/* 

===========
== SWELL ==
===========

Ten kod jest głównym sterownikiem modułu żaluzji - złożonego z N żaluzji oraz 1 wałka crescendo.
Aby zmienić domyślną ilość żaluzji - zmień N_SWELLS.

Żaluzje działają od kanału 11 w górę, kanały są zależny od ilości żaluzji (N_SWELLS). Przykładowo, dla N_SWELLS = 2, żaluzje są na kanałach 11 oraz 12.
Ilość żaluzji może być zmieniana, z zakresu od 1 do 4.
Ilość pozycji każdej z żaluzji może być programowalna, z zakresu 2 - 127.
Crescendo działa na kanale 10. Ilość pozycji wałka może być programowalna z zakresu 2 - 127.

Drgania styków zostaną wyeliminowanie poprzez hardware - potrzebne będą małe kondensatory (np. 100 nF)
*/

#include <errorCodes.h>
#include <ports.h>
#include <constants.h>

const unsigned int POTENTIOMETER_MIN = 0;
const unsigned int POTENTIOMETER_MAX = 1024;
const unsigned char POTENTIOMETER_BOUNCE = 4;

unsigned char N_SWELLS = 1;
unsigned char SWELL_POSITIONS[MAX_SWELLS] = { 8, 8, 8, 8 };
unsigned char SWELL_PINS[MAX_SWELLS] = { A0, A1, A2, A3 }; // Piny potencjometrów żaluzji

const unsigned char CRESCENDO_PIN = 4;
unsigned char CRESCENDO_POSITIONS = 16;

const unsigned char INPUT_PIN = 0;
const unsigned char OUTPUT_PIN = 1;
const unsigned char BUTTON_PIN = 2;
const unsigned char LED_PIN = 3;

unsigned int curSwellValues[MAX_SWELLS] = { 0, 0, 0, 0 };
unsigned int lastSwellValues[MAX_SWELLS] { 0, 0, 0, 0 };
unsigned int curCrescendoValue = 0;
unsigned int lastCrescendoValue = 0;

volatile bool crescendoActive = true;

// Zmienia ilość pozycji danej żaluzji
char changeSwellPositions(char swellIndex, char amount) {
    if (swellIndex < MIN_SWELLS || swellIndex > N_SWELLS)
        return WRONG_SWELL_INDEX;

    if (amount < MIN_SWELL_POSITIONS)
        return TOO_FEW_SWELL_POSITIONS;
    if (amount >= MAX_SWELL_POSITIONS)
        return TOO_MANY_SWELL_POSITIONS;

    SWELL_POSITIONS[swellIndex] = amount;

    return OK;
}

// Zmienia ilość pozycji wałka crescendo
char changeCrescendoPositions(char amount) {
    if (amount < MIN_CRESCENDO_POSITIONS)
        return TOO_FEW_CRESCENDO_POSITIONS;
    if (amount >= MAX_CRESCENDO_POSITIONS)
        return TOO_MANY_CRESCENDO_POSITIONS;
    
    CRESCENDO_POSITIONS = amount;

    return OK;
}

// Zmienia ilość żaluzji
char changeNSwells (char newAmount) {
    if (newAmount < MIN_SWELLS)
        return TOO_FEW_SWELLS;
    if (newAmount > MAX_SWELLS)
        return TOO_MANY_SWELLS;

    N_SWELLS = newAmount;

    return OK;
}

char potentiometerToMidiValue(int value, char maxPositions) {
    if (value < POTENTIOMETER_MIN)
        value = POTENTIOMETER_MIN;
    else if (value > POTENTIOMETER_MAX)
        value = POTENTIOMETER_MAX;

    int calculated = value / (POTENTIOMETER_MAX / maxPositions);

    return calculated < 0 ?
        0 : (calculated > 127 ?
            127 : calculated);
}

void swellsLogic() {
    for (int index = 0; index < N_SWELLS; index++) {
        unsigned char pin = SWELL_PINS[index];
        unsigned int lastValue = lastSwellValues[index];     
        unsigned int value = analogRead(pin);
        curSwellValues[index] = value;

        if (value > lastValue + POTENTIOMETER_BOUNCE || value < lastValue - POTENTIOMETER_BOUNCE) {            
            unsigned char channel = SWELL_START_CHANNEL + index;
            unsigned char maxPositions = SWELL_POSITIONS[index];

            setOutput(pin, value, channel, maxPositions);            
            lastSwellValues[index] = value;
        }
    }
}

void crescendoLogic() {
    int value = analogRead(CRESCENDO_PIN);
    curCrescendoValue = value;

    if (value > lastCrescendoValue + POTENTIOMETER_BOUNCE || value < lastCrescendoValue - POTENTIOMETER_BOUNCE) {
        //setOutput(CRESCENDO_PIN, value, CRESCENDO_CHANNEL, CRESCENDO_POSITIONS);
        lastCrescendoValue = curCrescendoValue;
    }    
}

void buttonLogic() {
    if (digitalRead(BUTTON_PIN) == LOW) {
        crescendoActive = !crescendoActive;        
        digitalWrite(LED_PIN, crescendoActive ? LOW : HIGH);
    }
}

void setOutput(char pin, int value, char channel, char maxPositions) {
    unsigned char calculated = potentiometerToMidiValue(value, maxPositions);
    unsigned char MIDI_value = ((VALUE_MAX / (maxPositions - 1)) + 1) * (calculated);
    MIDI_value = MIDI_value > VALUE_MAX ? VALUE_MAX : (MIDI_value < VALUE_MIN ? VALUE_MIN : MIDI_value);

    //sendMidi(CC[channel], channel, MIDI_value);

    Serial.print((int)pin);
    Serial.print(" ");
    Serial.print((int)value);
    Serial.print(" ");
    Serial.print((int)calculated);
    Serial.print(" ");
    Serial.print((int)MIDI_value);
    Serial.print(" ");
    Serial.println((int)maxPositions);
}

void sendMidi(char message, char channel, char value) {
    Serial.write(message);
    Serial.write(channel);
    Serial.write(value);    
}

void readMidi() {
    if (Serial.available()) {
        char command = Serial.read();

        if (command == 0x8F && command == 0x9F) {
            char note = Serial.read();
            char velocity = Serial.read();

            char channel = (command & 0x0F);
            char type = command & 0xF0;

            if (channel == ERR_CHANNEL) {
                char result = OK;

                switch (note) {
                    case CHANGE_N_SWELLS:
                        result = changeNSwells(velocity);
                        break;
                    case CHANGE_CRESCENDO_POSITIONS:
                        result = changeCrescendoPositions(velocity);
                        break;
                    case CHANGE_SWELL_POSITIONS_1:
                        result = changeSwellPositions(0, velocity);
                        break;
                    case CHANGE_SWELL_POSITIONS_2:
                        result = changeSwellPositions(1, velocity);
                        break;
                    case CHANGE_SWELL_POSITIONS_3:
                        result = changeSwellPositions(2, velocity);
                        break;
                    case CHANGE_SWELL_POSITIONS_4:
                        result = changeSwellPositions(3, velocity);
                        break;
                }

                Serial.write(ON[ERR_CHANNEL]);
                Serial.write(result);
                Serial.write(VALUE_MAX);
            }
        }
    }
}

// Inicjalizacja
void setup() {
    Serial.begin(115200);
    pinMode(BUTTON_PIN, INPUT_PULLUP);
    pinMode(LED_PIN, OUTPUT);
}

// Główna pętla
void loop() {
    swellsLogic();
    crescendoLogic();
    buttonLogic();
}
