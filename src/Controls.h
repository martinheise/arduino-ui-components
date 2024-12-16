/*
  controls.h - Library proving functionality to control parameters
*/
#ifndef UI_CONTROLS_h
#define UI_CONTROLS_h

#include <Arduino.h>

/*
 * callback function called on changed value
 */
using ChangeCallback = void (*)(int value, byte id);

/**
 * an analog input, e.g. from a potentiometer, setting a value.
 * In pass-through mode, changes from the input only get effective once the current value is crossed/touched,
 * this is helpful when the value is also set externally and you want to avoid jumps when using the control
 */
class Control {
public:
    /// simple construct with pin number
    Control(uint8_t p);
    /// construct with pin number and min/max for output value range
    Control(uint8_t p, int min, int max);
    /// construct with pin number, min/max for output value range and passThroughMode
    Control(uint8_t p, int min, int max, bool pm);
    /// set output value range
    void setMinMax(int min, int max);
    /// set passThrough mode
    void setPassThroughMode(bool m);
    /// set current value and reset for pass-through mode
    void setValue(int val);
    /// set current value and optionally reset for pass-through mode
    void setValue(int val, bool reset);
    /// get current value
    int getValue();
    /// update the control and check for changes, usually called from main loop()
    void loop();
    /// set a handler for value changes, the optional id will be passed to the callback
    void setChangeHandler(ChangeCallback fptr);
    void setChangeHandler(ChangeCallback fptr, byte id);
    /// configuration: maximum input value to expected, depending on hardware
    static unsigned int inputRange;
    /// configuration: ignore some values at lower and higher end to assure the whole output range is used with non-ideal potentiometers
    static unsigned int inputEdges;
private:
    uint8_t pin;
    int value{0};
    int minValue{0};
    int maxValue{255};
    int currInput{0};
    bool passThroughMode{false};
    bool isActive{true};
    ChangeCallback _changeCallback = nullptr;
    byte _callbackId{0};
    // map analog input to value
    int input2value(int input);
};

#endif //UI_CONTROLS_h
