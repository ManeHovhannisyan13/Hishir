#include "Buzzer.h"

void Buzzer::init() {
    if (_pin != -1) {
        pinMode(_pin, OUTPUT);
        off();
    }
}

void Buzzer::on() {
    digitalWrite(_pin, BUZZER_ACTIVE_LOW ? LOW : HIGH);
}

void Buzzer::off() {
    digitalWrite(_pin, BUZZER_ACTIVE_LOW ? HIGH : LOW);
}

void Buzzer::blink() {
    if (_pin == -1) return;

    unsigned long now = millis();

    if (now - buzzerPrevMs >= (unsigned long)buzzerInterval) {
        buzzerPrevMs = now;
        buzzerBlinkState = !buzzerBlinkState;

        if (buzzerBlinkState) {
            on();
        } else {
            off();
        }
    }
}
