#include "Controls.h"

// set defaults for input range
#if defined(ESP_PLATFORM)
unsigned int inputRange{4095};
#else
unsigned int Control::inputRange{1023};
#endif

unsigned int Control::inputEdges{5};


Control::Control(uint8_t p) : pin(p) {}

Control::Control(uint8_t p, int min, int max) : pin(p), minValue(min), maxValue(max) {}

Control::Control(uint8_t p, int min, int max, bool pm) : pin(p), minValue(min), maxValue(max), passThroughMode(pm) {}


void Control::setChangeHandler(ChangeCallback fptr) {
    setChangeHandler(fptr, 0);
}

void Control::setChangeHandler(ChangeCallback fptr, byte id) {
    _changeCallback = fptr;
    _callbackId = id;
}

void Control::setMinMax(int min, int max) {
    minValue = min;
    maxValue = max;
}

void Control::setPassThroughMode(bool m) {
    passThroughMode = m;
}

void Control::setValue(int val) {
    setValue(val, true);
}

void Control::setValue(int val, bool reset) {
    value = constrain(val, minValue, maxValue);
    if (reset && passThroughMode) {
        isActive = false;
    }
    loop();
}

int Control::getValue() {
    return value;
}

int Control::input2value(int input) {
    unsigned int minInput = inputEdges;
    unsigned int maxInput = inputRange - inputEdges;
    int val = map(input, minInput, maxInput, minValue, maxValue + 1); // + 1 for better rounding on small ranges
    val = constrain(val, minValue, maxValue);
    return val;
}

void Control::loop() {
    int input = analogRead(pin);
    // check pass-through activation
    if (!isActive && passThroughMode) {
        if ((input2value(currInput) < value && input2value(input) >= value) ||
            (input2value(currInput) > value && input2value(input) <= value)) {
            isActive = true;
        }
    }
    if (isActive || !passThroughMode) {
        int val = input2value(input);
        if (val != value) {
            value = val;
            if (_changeCallback) {
                _changeCallback(value, _callbackId);
            }
        }
    }
    currInput = input;
}
