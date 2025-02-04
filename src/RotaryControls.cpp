#include "RotaryControls.h"

RotaryControl::RotaryControl(uint8_t pclk, uint8_t pdt) : pinClk(pclk), pinDt(pdt) {
    pinMode(pclk, INPUT);
    pinMode(pdt, INPUT);
    prevClk = digitalRead(pinClk);
}

RotaryControl::RotaryControl(uint8_t pclk, uint8_t pdt, int min, int max) : pinClk(pclk), pinDt(pdt), minValue(min), maxValue(max) {
    pinMode(pclk, INPUT);
    pinMode(pdt, INPUT);
    prevClk = digitalRead(pinClk);
}

void RotaryControl::setMinMax(int min, int max) {
    minValue = min;
    maxValue = max;
}

void RotaryControl::setStep(int st) {
    step = st;
}

int RotaryControl::getStep() {
    return step;
}

void RotaryControl::setRoundToStep(bool rts) {
    roundToStep = rts;
}

bool RotaryControl::getRoundToStep() {
    return roundToStep;
}


void RotaryControl::setValue(int val) {
    value = constrain(val, minValue, maxValue);
}

int RotaryControl::getValue() {
    return value;
}

void RotaryControl::loop() {
    int clk = digitalRead(pinClk);

    if (clk != prevClk) {
        bool dir = digitalRead(pinDt) != clk;
        int val = value;
        if (dir) {
            // increment
            val = val + step;
        } else {
            val = val - step;
        }
        if (roundToStep && (val % step) > 0) {
            val = int(round(val / step)) * step;
        }
        val = constrain(val, minValue, maxValue);
        if (val != value) {
            value = val;
            if (_changeCallback) {
                _changeCallback(value, _callbackId, dir);
            }
        }
    }
    prevClk = clk;
}

void RotaryControl::setChangeHandler(RotaryChangeCallback fptr) {
    setChangeHandler(fptr, 0);
}

void RotaryControl::setChangeHandler(RotaryChangeCallback fptr, byte id) {
    _changeCallback = fptr;
    _callbackId = id;
}
