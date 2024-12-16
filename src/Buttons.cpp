#include "Buttons.h"

unsigned int Button::longPressTime{2000};
unsigned int Button::debounceTime{20};

Button::Button(uint8_t p) {
    pin = p;
}

void Button::setPressedHandler(ButtonCallback fptr) {
    setPressedHandler(fptr, 0);
}

void Button::setPressedHandler(ButtonCallback fptr, byte id) {
    _clickCallback = fptr;
    _callbackId = id;
}

void Button::setLongPressedHandler(ButtonCallback fptr) {
    setLongPressedHandler(fptr, 0);
}

void Button::setLongPressedHandler(ButtonCallback fptr, byte id) {
    _longClickCallback = fptr;
    _longCallbackId = id;
}

void Button::setValue(bool val) {
    value = val;
}

bool Button::getValue() {
    return value;
}

bool Button::isPressed() {
    return pressed;
}

void Button::loop() {
    int input = digitalRead(pin);

    if (input != _lastState) {
        _debounceTimer = millis();
    }

    // only do anything after debounce time
    if ((millis() - _debounceTimer) > debounceTime) {
        // start timing on button down
        if (input && input != pressed) {
            _timer = millis();
        }
        // long click callback after duration while still pressed
        if (pressed && _timer > 0 && _longClickCallback && ((millis() - _timer) > longPressTime)) {
            _longClickCallback(_longCallbackId);
            _timer = 0;
        }
        if (!input && input != pressed) {
            value = !value;
        }
        // callback on button up, if not handled by longclick
        if (!input && input != pressed && _timer > 0) {
            if (_clickCallback) {
                _clickCallback(_callbackId);
            }
        }
        pressed = input;
    }
    _lastState = input;
}
