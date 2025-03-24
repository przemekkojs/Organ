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

Drgania styków zostaną wyeliminowanie poprzez hardware - potrzebne będą małe kondensatory (np. 1 uF, jak trzeba więcej to 2.2uF - 4.7uF)
*/

#include <errorCodes.h>
#include <ports.h>
#include <constants.h>

const uint16_t POTENTIOMETER_MAX = 1024;
const uint8_t POTENTIOMETER_MIN = 0;
const uint8_t POTENTIOMETER_BOUNCE = 8;
const float ALPHA = 0.1;

uint8_t N_SWELLS = 4;
uint8_t SWELL_POSITIONS[MAX_SWELLS] = { 8, 8, 8, 8 };
uint8_t SWELL_PINS[MAX_SWELLS] = { A0, A1, A2, A3 }; // Piny potencjometrów żaluzji

const uint8_t CRESCENDO_PIN = 4;
uint8_t CRESCENDO_POSITIONS = 16;

const uint8_t INPUT_PIN = 0;
const uint8_t OUTPUT_PIN = 1;
const uint8_t BUTTON_PIN = 2;
const uint8_t LED_PIN = 3;

uint16_t curSwellValues[MAX_SWELLS] = { 0, 0, 0, 0 };
uint16_t lastSwellValues[MAX_SWELLS] { 0, 0, 0, 0 };
uint16_t curCrescendoValue = 0;
uint16_t lastCrescendoValue = 0;

volatile bool crescendoActive = true;

// Zmienia ilość pozycji danej żaluzji
uint8_t changeSwellPositions(uint8_t swellIndex, uint8_t amount) {
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
uint8_t changeCrescendoPositions(uint8_t amount) {
    if (amount < MIN_CRESCENDO_POSITIONS)
        return TOO_FEW_CRESCENDO_POSITIONS;
    if (amount >= MAX_CRESCENDO_POSITIONS)
        return TOO_MANY_CRESCENDO_POSITIONS;
    
    CRESCENDO_POSITIONS = amount;

    return OK;
}

// Zmienia ilość żaluzji
uint8_t changeNSwells(uint8_t newAmount) {
    if (newAmount < MIN_SWELLS)
        return TOO_FEW_SWELLS;
    if (newAmount > MAX_SWELLS)
        return TOO_MANY_SWELLS;

    N_SWELLS = newAmount;

    return OK;
}

uint8_t potentiometerToMidiValue(uint16_t value, uint8_t maxPositions) {
    if (value < POTENTIOMETER_MIN)
        value = POTENTIOMETER_MIN;
    else if (value > POTENTIOMETER_MAX)
        value = POTENTIOMETER_MAX;

    uint16_t calculated = value / (POTENTIOMETER_MAX / maxPositions);

    return calculated < 0 ?
        0 : (calculated > 127 ?
            127 : calculated);
}

/*
 * Tak naprawdę implementacja prostego LPF - Low Pass Filter - Filtr dolnoprzepustowy
 * ALPHA - współczynnik tłumienia. Sygnał zbyt skokowy -> zmniejszamy alpha. Zbyt wolna reakcja filtra -> zwiększamy alpha.
 */
uint16_t smoothen(uint16_t newValue, uint16_t lastValue) {
    return (ALPHA * newValue) + ((1.0 - ALPHA) * lastValue);
}

void swellsLogic() {
    for (int index = 0; index < N_SWELLS; index++) {
        uint8_t pin = SWELL_PINS[index];
        uint16_t lastValue = lastSwellValues[index];     
        uint16_t rawValue = analogRead(pin);
        uint16_t value = smoothen(rawValue, lastValue);

        curSwellValues[index] = value;

        int16_t tmp = lastValue - POTENTIOMETER_BOUNCE;
        tmp = tmp < 0 ? 0 : tmp;

        bool differ = value != lastValue;
        bool higher = value > lastValue + POTENTIOMETER_BOUNCE;
        bool lower = value < tmp;

        if (differ && (lower || higher)) {
            // if (lower)
            //     Serial.print("lower - ");
            // if (higher)
            //     Serial.print("higher - ");

            // Serial.print(index);
            // Serial.print(": ");
            // Serial.print(value);
            // Serial.print(" ");
            // Serial.print(lastValue);
            // Serial.print(" ");
            // Serial.print(lastValue + POTENTIOMETER_BOUNCE);
            // Serial.print(" ");
            // Serial.println(tmp);

            uint8_t channel = SWELL_START_CHANNEL + index;
            uint8_t maxPositions = SWELL_POSITIONS[index];

            setOutput(pin, value, channel, maxPositions);            
            lastSwellValues[index] = value;
        }
    }
}

void crescendoLogic() {
    // TODO: Wersja dla enkodera
}

void buttonLogic() {
    if (digitalRead(BUTTON_PIN) == LOW) {
        crescendoActive = !crescendoActive;        
        digitalWrite(LED_PIN, crescendoActive ? LOW : HIGH);
    }
}

void setOutput(uint8_t pin, uint16_t value, uint8_t channel, uint8_t maxPositions) {
    uint8_t calculated = potentiometerToMidiValue(value, maxPositions);
    uint8_t MIDI_value = ((VALUE_MAX / (maxPositions - 1)) + 1) * (calculated);

    MIDI_value = MIDI_value > VALUE_MAX ?
        VALUE_MAX : (MIDI_value < VALUE_MIN ?
            VALUE_MIN : MIDI_value);

    sendMidi(CC[channel], channel, MIDI_value);

    // Serial.print((uint16_t)pin);
    // Serial.print(" ");
    // Serial.print((uint16_t)value);
    // Serial.print(" ");
    // Serial.print((uint16_t)calculated);
    // Serial.print(" ");
    // Serial.print((uint16_t)MIDI_value);
    // Serial.print(" ");
    // Serial.println((uint16_t)maxPositions);
}

void sendMidi(uint8_t message, uint8_t channel, uint8_t value) {
    Serial.write(message);
    Serial.write(channel);
    Serial.write(value);    
}

void readMidi() {
    if (Serial.available()) {
        uint8_t command = Serial.read();

        if (command == 0x8F && command == 0x9F) {
            uint8_t note = Serial.read();
            uint8_t velocity = Serial.read();

            uint8_t channel = (command & 0x0F);
            uint8_t type = command & 0xF0;

            if (channel == ERR_CHANNEL) {
                uint8_t result = OK;

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
    Serial.begin(115200); //31250 - baud rate dla MIDI. 115200 - baud rate dla hairless-serial.
    pinMode(BUTTON_PIN, INPUT_PULLUP);
    pinMode(LED_PIN, OUTPUT);
}

// Główna pętla
void loop() {
    swellsLogic();
    crescendoLogic();
    buttonLogic();
}
