#ifndef UI_BUTTONS_h
#define UI_BUTTONS_h

#include "Arduino.h"

/*
 * callback function called for pressed buttons
 */
using ButtonCallback = void (*)(byte id);

/**
 * simple push button, executing callback functions when the button is pressed
 * additional handles a boolean value, toggled whenever the button is pressed
 */
class Button {
public:
    /// construct with pin number
    Button(uint8_t p);
    /// set current value
    void setValue(bool val);
    /// get current value
    bool getValue();
    /// get current (debounced) pressed state
    bool isPressed();
    /// update the button and check for changes, usually called from main loop()
    void loop();
    /// set a handler for pressed button (on button up!), the optional id will be passed to the callback
    void setPressedHandler(ButtonCallback fptr);
    void setPressedHandler(ButtonCallback fptr, byte id);
    /// set a handler for longer hold button, the optional id will be passed to the callback
    void setLongPressedHandler(ButtonCallback fptr);
    void setLongPressedHandler(ButtonCallback fptr, byte id);
    /// configuration: time until long press is triggered
    static unsigned int longPressTime;
    /// configuration: time for debouncing
    static unsigned int debounceTime;
private:
    uint8_t pin;
    bool pressed{false}; // debounced pressed state
    bool value{false};
    ButtonCallback _clickCallback = nullptr;
    ButtonCallback _longClickCallback = nullptr;
    byte _callbackId{0};
    byte _longCallbackId{0};
    unsigned long _timer{0};
    unsigned long _debounceTimer{0};
    bool _lastState{false};
};

#endif //UI_BUTTONS_h
