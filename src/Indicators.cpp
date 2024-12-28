#include "Indicators.h"

unsigned long Indicator::blinkStart{0};
unsigned long Indicator::fastBlinkStart{0};

// default configuration
unsigned int Indicator::blinkOnTime = 700;
unsigned int Indicator::blinkOffTime = 300;
unsigned int Indicator::fastBlinkOnTime = 150;
unsigned int Indicator::fastBlinkOffTime = 150;
unsigned int Indicator::notificationBlinkTime = 1800;
unsigned int Indicator::singleFlashTime = 100;

void Indicator::setStatus(Indicator::status s) {
    currStatus = s;
    switch (currStatus) {
        case ON:
            switchOn();
            break;
        case BLINK:
            // todo: OPT reset start if no blinking LEDs (static blinkCount ...)
            if (blinkStart == 0) {
                blinkStart = millis();
            }
            break;
        case FAST_BLINK:
            if (fastBlinkStart == 0) {
                fastBlinkStart = millis();
            }
            break;
        default:
            switchOff();
    }
}

Indicator::status Indicator::getStatus() {
    return currStatus;
}

void Indicator::notificationBlink() {
    notificationBlinkStart = millis();
}

void Indicator::singleFlash() {
    singleFlashStart = millis();
}

void Indicator::loop() {

    bool state = (currStatus == ON);

    if (notificationBlinkStart > 0) {
        unsigned long blinkTime = millis() - notificationBlinkStart;
        // notification blink ended
        if (blinkTime > notificationBlinkTime) {
            notificationBlinkStart = 0;
        } else {
            state = blinkTime % (fastBlinkOnTime + fastBlinkOffTime) < fastBlinkOnTime;
        }
    } else if (singleFlashStart > 0) {
        unsigned long blinkTime = millis() - singleFlashStart;
        // singleFlash ended
        if (blinkTime > singleFlashTime) {
            singleFlashStart = 0;
        } else {
            state = currStatus != ON;
        }
    } else if (currStatus == BLINK) {
        state = (millis() - blinkStart) % (blinkOnTime + blinkOffTime) < blinkOnTime;
    } else if (currStatus == FAST_BLINK) {
        state = (millis() - fastBlinkStart) % (fastBlinkOnTime + fastBlinkOffTime) < fastBlinkOnTime;
    }
    if (state) {
        switchOn();
    } else {
        switchOff();
    }
}

void Indicator::switchOn() {
    // not implemented
}

void Indicator::switchOff() {
    // not implemented
}



LedIndicator::LedIndicator(uint8_t p) {
    pin = p;
    pinMode(pin, OUTPUT);
    setStatus(Indicator::OFF);
}

void LedIndicator::switchOn() {
    digitalWrite(pin, HIGH);
}

void LedIndicator::switchOff() {
    digitalWrite(pin, LOW);
}



RGBLedIndicator::RGBLedIndicator(uint8_t pr, uint8_t pg, uint8_t pb) {
    pins[0] = pr;
    pins[1] = pg;
    pins[2] = pb;
    for (unsigned char p : pins) {
        pinMode(p, OUTPUT);
    }
    setStatus(Indicator::OFF);
}

RGBLedIndicator::rgbColor RGBLedIndicator::getColor() {
    return color;
}

void RGBLedIndicator::setColor(RGBLedIndicator::rgbColor c) {
    color = c;
}

void RGBLedIndicator::setColor(uint8_t r, uint8_t g, uint8_t b) {
    color.r = r;
    color.g = g;
    color.b = b;
}

void RGBLedIndicator::switchOn() {
    analogWrite(pins[0], color.r);
    analogWrite(pins[1], color.g);
    analogWrite(pins[2], color.b);
}

void RGBLedIndicator::switchOff() {
    for (unsigned char p : pins) {
        digitalWrite(p, LOW);
    }
}
