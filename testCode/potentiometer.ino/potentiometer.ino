const int POTENTIOMETER = A0;
const int LED1 = 9;
const int LED2 = 7;
const int BTN = 8;
const int POT_MARGIN = 2;
const int BTN_DEBOUNCE = 50;

void setup() {
    pinMode(BTN, INPUT_PULLUP);
    pinMode(LED1, OUTPUT);
    pinMode(LED2, OUTPUT);
}

int potLast = 0;
int btnLast = LOW;
long long btnTimer = 0;
bool on = true;
bool low = false;

bool buttonPressed(int pin) {
    int btnRead = digitalRead(pin);
    btnTimer++;

    if (btnTimer >= BTN_DEBOUNCE) {
        if (btnRead == LOW) {
            low = true;
        }
        else if (btnRead == HIGH) {
            btnTimer = 0;
            bool tmp = low;
            low = false;
            return tmp;
        }
    }   

    return false;
}

void loop() {
    if (buttonPressed(BTN)) {
        on = !on;
        digitalWrite(LED2, on ? HIGH : LOW);
    }

    if (on) {
        int potCurrent = analogRead(POTENTIOMETER);

        if (potCurrent > (potLast + POT_MARGIN) || potCurrent < (potLast - POT_MARGIN)) {
            potLast = potCurrent;
            analogWrite(LED1, potCurrent / 4);
        }
    }    
}
