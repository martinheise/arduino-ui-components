#include "Buttons.h"

unsigned int Button::longPressTime{2000};
unsigned int Button::debounceTime{20};

Button::Button(uint8_t p) : pin(p) {
    pinMode(pin, INPUT);
}

Button::Button(uint8_t p, uint8_t pinmode) : pin(p) {
    _pressedRead = (pinmode & INVERTED_INPUT) > 0 || pinmode == INPUT_PULLUP;
    pinmode = pinmode & 0x7F;
#ifdef INPUT_PULLDOWN
    if (pinmode != INPUT_PULLUP && pinmode != INPUT_PULLDOWN) {
#else
    if (pinmode != INPUT_PULLUP) {
#endif
        pinmode = INPUT;
    }
    pinMode(pin, pinmode);
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
    // read and consider _pressedRead
    bool input = digitalRead(pin) xor _pressedRead;

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
        // change value on button up
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
