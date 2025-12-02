#include <Adafruit_MCP23X17.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <MIDIUSB.h>

#define READ_PIN(port, bit) ((port & (1 << bit)) != 0)

struct Debounce {
    bool lastState;
    unsigned long lastChange;
};

struct AnalogDebounce {
    int lastValue;
    unsigned long lastChange;
};

bool debounce(Debounce &d, bool current, unsigned long debounceTime) {
    if (current != d.lastState) {
        d.lastChange = millis();
        d.lastState = current;
        return false;
    }

    return (millis() - d.lastChange) > debounceTime;
}

bool analogDebounce(AnalogDebounce &d, int current, int threshold, unsigned long debounceTime) {
    if (abs(current - d.lastValue) > threshold) {
        d.lastChange = millis();
        d.lastValue = current;

        return false;
    }

    return (millis() - d.lastChange) > debounceTime;
}

constexpr uint8_t MIDI_MIN = 0;
constexpr uint8_t MIDI_MAX = 127;
constexpr uint16_t POTENTIOMETER_MAX = 1023;

constexpr uint8_t COMBINATION_INDEX = 9;
constexpr uint8_t COMBINATION_ROW = 0;
constexpr uint8_t COMBINATION_MIN = 0;
constexpr uint16_t COMBINATION_MAX = 999;
uint16_t currentCombination = 0;

constexpr uint8_t N_MCP = 2;
constexpr uint8_t BTNS_PER_MCP = 10;
constexpr uint8_t N_SWELLS = 2;
constexpr uint8_t MAX_N_SWELLS = 4;
constexpr uint8_t SWELL_ROW = 3;

constexpr uint8_t SWELL_PINS[MAX_N_SWELLS] = {A0, A1, A2, A3};
constexpr uint8_t LED_PINS[N_MCP] = { BTNS_PER_MCP, BTNS_PER_MCP };
constexpr uint8_t BUTTON_PINS[N_MCP] = { BTNS_PER_MCP, BTNS_PER_MCP };

uint16_t mcp_led_state[N_MCP] = {0, 0};
uint16_t last_mcp_led_state[N_MCP] = {-1, -1};
uint16_t mcp_button_state[N_MCP] = {0, 0};

constexpr unsigned long DEBOUNCE_TIME = 30;
constexpr unsigned long ANALOG_INTERVAL = 20;
constexpr int ANALOG_THRESHOLD = 20;

constexpr uint8_t CRESCENDO_CLK = 4;
constexpr uint8_t CRESCENDO_DT = 5;
constexpr uint8_t CRESCENDO_INDEX = 9;
constexpr uint8_t CRESCENDO_ROW = 1;
constexpr uint8_t CRESCENDO_MAX = 32;
constexpr uint8_t CRESCENDO_MIN = 0;
constexpr uint8_t CRESCENDO_SPEED = 1;

constexpr uint8_t MIDI_CHANNEL = 0;
constexpr uint8_t MIDI_VELOCITY = 127;
constexpr uint8_t MIDI_CRESC = 20;

constexpr uint8_t MIDI_BUTTON_CODES[N_MCP][BTNS_PER_MCP] = {
    {108, 109, 110, 111, 112, 113, 114, 115, 116, 117},
    {118, 119, 120, 121, 122, 123, 124, 125, 126, 127}
};

int crescendoLevel = 0;
bool crescendoOn = true;
bool lastCrescendoState = HIGH;
unsigned long CRESCENDO_LAST_DEBOUNCE_TIME = 0;

Adafruit_MCP23X17 mcp_btn[N_MCP];
Adafruit_MCP23X17 mcp_led[N_MCP];
LiquidCrystal_I2C lcd(0x26, 20, 4);

Debounce buttonDebounce[N_MCP][BTNS_PER_MCP];
AnalogDebounce swellDebounce[MAX_N_SWELLS];

bool BUTTON_CURRENT_STATES[N_MCP][BTNS_PER_MCP] = {
    { HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH },
    { HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH }
};

bool BUTTON_ON[N_MCP][BTNS_PER_MCP] = {
    { true, true, true, true, true, true, true, true, true, true },
    { HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH }
};

uint16_t SWELL_LAST_VALUES[MAX_N_SWELLS] = {0, 0, 0, 0};

void noteOn(byte pitch) {
    midiEventPacket_t noteOn = {0x09, 0x90 | MIDI_CHANNEL, pitch, MIDI_VELOCITY};
    MidiUSB.sendMIDI(noteOn);
}

void noteOff(byte pitch) {
    midiEventPacket_t noteOff = {0x08, 0x80 | MIDI_CHANNEL, pitch, MIDI_VELOCITY};
    MidiUSB.sendMIDI(noteOff);
}

void controlChange(byte device, byte value) {
    midiEventPacket_t event = {0x0B, 0xB0 | MIDI_CHANNEL, device, value};
    MidiUSB.sendMIDI(event);
}

int realCrescendoValue() {
    return crescendoLevel / CRESCENDO_SPEED;
}

int potentiometerToMidiValue(uint16_t val) {
    int result = val / (POTENTIOMETER_MAX / MIDI_MAX);

    if (result < MIDI_MIN)
        return MIDI_MIN;
    if (result >= MIDI_MAX)
        return MIDI_MAX;
    
    return result;
}

int potentiometerToSwellValue(uint16_t val) {
    return val / (POTENTIOMETER_MAX / 10);
}

void printCrescendo() {
    static int lastPrinted = -1;
    int real = realCrescendoValue();

    if (real != lastPrinted) {
        char buff[8];
        snprintf(buff, sizeof(buff), "%3d", real);
        lcd.setCursor(CRESCENDO_INDEX + 3, CRESCENDO_ROW);
        lcd.print(buff);
        lastPrinted = real;
    }
}

void printSwellValue(int index, int swellValue) {
    static int lastSwell[MAX_N_SWELLS] = {-1, -1, -1, -1};

    if (swellValue != lastSwell[index]) {
        char buff[8];
        snprintf(buff, sizeof(buff), "%3d", swellValue);
        lcd.setCursor(3, index);
        lcd.print(buff);
        lastSwell[index] = swellValue;
    }
}

void printCombination() {
    char buff[8];
    snprintf(buff, sizeof(buff), "%3d", currentCombination);
    lcd.setCursor(COMBINATION_INDEX + 3, COMBINATION_ROW);
    lcd.print(buff);
}

void init_states_and_debounce() {
    for (int i = 0; i < N_MCP; ++i) {
        for (int j = 0; j < BTNS_PER_MCP; ++j) {
            BUTTON_CURRENT_STATES[i][j] = HIGH;
            BUTTON_ON[i][j] = true;
            buttonDebounce[i][j].lastState = BUTTON_CURRENT_STATES[i][j];
            buttonDebounce[i][j].lastChange = millis();
        }
    }

    for (int i = 0; i < MAX_N_SWELLS; ++i) {
        swellDebounce[i].lastValue = analogRead(SWELL_PINS[i]);
        swellDebounce[i].lastChange = millis();
    }
}

void setup() {
    ADCSRA = (ADCSRA & 0b11111000) | 0x04;

    Wire.begin();
    init_states_and_debounce();

    lcd.init();
    lcd.backlight();
    lcd.clear();
    lcd.setCursor(CRESCENDO_INDEX, CRESCENDO_ROW);
    lcd.print("CR:");
    lcd.setCursor(COMBINATION_INDEX, COMBINATION_ROW);
    lcd.print("CB:");

    printCombination();
    printCrescendo();

    for (int i = 0; i < N_SWELLS; i++) {
        lcd.setCursor(0, i);
        lcd.print("SW");
        lcd.print(i);
        lcd.print("  0");
    }

    for (int i = 0; i < N_MCP; i++) {
        int addr_btn = 0x20 + i * 2 + 1;
        int addr_led = 0x20 + i * 2;

        mcp_led[i].begin_I2C(addr_led);
        delay(5);
        mcp_btn[i].begin_I2C(addr_btn);
        delay(5);

        int btn_count = BUTTON_PINS[i];
        int led_count = LED_PINS[i];

        for (int pin = 0; pin < btn_count; pin++)
            mcp_btn[i].pinMode(pin, INPUT);

        for (int pin = 0; pin < led_count; pin++)
            mcp_led[i].pinMode(pin, OUTPUT);
    }

    for (int i = 0; i < N_SWELLS; i++) {
        pinMode(SWELL_PINS[i], INPUT);
    }

    pinMode(CRESCENDO_DT, INPUT_PULLUP);
    pinMode(CRESCENDO_CLK, INPUT_PULLUP);
    lastCrescendoState = digitalRead(CRESCENDO_CLK);
}

void loop() {
    unsigned long now = millis();

    if (crescendoOn) {
        bool currentState = digitalRead(CRESCENDO_CLK);

        if (currentState != lastCrescendoState) {        
            bool dtState = digitalRead(CRESCENDO_DT);
            int delta = (dtState != currentState) ? 1 : -1;

            if (now - CRESCENDO_LAST_DEBOUNCE_TIME > DEBOUNCE_TIME) {
                int newLevel = constrain(crescendoLevel + delta, CRESCENDO_MIN, CRESCENDO_MAX * CRESCENDO_SPEED);
                
                if (newLevel != crescendoLevel) {                    
                    crescendoLevel = newLevel;
                    controlChange(MIDI_CRESC, newLevel);
                    printCrescendo();
                }

                CRESCENDO_LAST_DEBOUNCE_TIME = now;
            }

            lastCrescendoState = currentState;
        }
    }

    for (int i = 0; i < N_MCP; i++) {
        mcp_button_state[i] = mcp_btn[i].readGPIOAB();

        int btn_count = BUTTON_PINS[i];
        int led_count = LED_PINS[i];

        for (int pin = 0; pin < btn_count; pin++) {
            bool reading = bitRead(mcp_button_state[i], pin);

            if (debounce(buttonDebounce[i][pin], reading, DEBOUNCE_TIME)) {
                if (reading != BUTTON_CURRENT_STATES[i][pin]) {
                    BUTTON_CURRENT_STATES[i][pin] = reading;

                    if (reading == LOW) {
                        BUTTON_ON[i][pin] = !BUTTON_ON[i][pin];
                        BUTTON_ON[i][pin] ? noteOff(MIDI_BUTTON_CODES[i][pin]) : noteOn(MIDI_BUTTON_CODES[i][pin]);

                        if (pin < led_count)
                            bitWrite(mcp_led_state[i], pin, BUTTON_ON[i][pin] ? LOW : HIGH);
                    }
                }
            }            
        }

        if (mcp_led_state[i] != last_mcp_led_state[i]) {
            last_mcp_led_state[i] = mcp_led_state[i];
            mcp_led[i].writeGPIOAB(mcp_led_state[i]);
        }            
    }    

    static unsigned long lastAnalogRead = 0;

    if (now - lastAnalogRead > ANALOG_INTERVAL) {
        lastAnalogRead = now;

        for (int i = 0; i < N_SWELLS; i++) {
            int reading = analogRead(SWELL_PINS[i]);

            if (analogDebounce(swellDebounce[i], reading, ANALOG_THRESHOLD, DEBOUNCE_TIME)) {
                int swellValue = potentiometerToSwellValue(reading);
                int midiSwellValue = potentiometerToMidiValue(reading);
                int lastMidiSwellValue = SWELL_LAST_VALUES[i];

                if (abs(midiSwellValue - lastMidiSwellValue) > 2)
                    controlChange(i + 16, midiSwellValue); // 16 bo 16-19 to CC GENERAL USE

                SWELL_LAST_VALUES[i] = midiSwellValue;
                printSwellValue(i, swellValue);
            }
        }
    }    

    static unsigned long lastFlush = 0;
    if (now - lastFlush >= 250) {
        MidiUSB.flush();
        lastFlush = now;
    }
}
