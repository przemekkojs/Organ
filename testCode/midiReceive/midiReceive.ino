const uint8_t LED = 3;
const uint8_t BTN = 2;

void setup() {
    pinMode(BTN, INPUT_PULLUP);
    pinMode(LED, OUTPUT);
    Serial.begin(31250);
}

uint8_t curBtn = HIGH;
uint8_t lastBtn = HIGH;

bool buttonPressed() {
    curBtn = digitalRead(BTN);

    if (curBtn == HIGH && lastBtn == LOW) {
        return true;
    }

    lastBtn = curBtn;
    return false;
}

void loop() {
    static byte midiMessage[3];
    static byte index = 0;

    if (Serial.available()) {
        byte incoming = Serial.read();

        if (incoming & 0x80) {  
            midiMessage[0] = incoming;
            index = 1;
        } 
        else {
            midiMessage[index] = incoming;
            index++;
            
            if (index == 3)
                processMIDI(midiMessage);
        }
    }
}

void processMIDI(byte *midiMsg) {
    byte command = midiMsg[0] & 0xF0;
    byte channel = midiMsg[0] & 0x0F;
    byte note = midiMsg[1];
    byte velocity = midiMsg[2];

    Serial.print((int)command);
    Serial.print(" ");
    Serial.print((int)channel);
    Serial.print(" ");
    Serial.print((int)note);
    Serial.print(" ");
    Serial.print((int)velocity);
    Serial.print(" ");
}