#ifndef UI_ROTARYCONTROL_H
#define UI_ROTARYCONTROL_H

#include <Arduino.h>

/*
 * callback function called on changed value
 * dir: true for clockwise (incrementing), false for counter-clockwise (decrementing)
 */
using RotaryChangeCallback = void (*)(int value, byte id);

/*
 * ToDo:
 *  - option to trigger callback only with delay (avoid fast changes)
 */

/**
 * Setting an integer value by an incremental rotary encoder
 */
class RotaryControl {
public:
    /// simple construct with two pins (clk + dt)
    RotaryControl(uint8_t pclk, uint8_t pdt);
    /// construct with pin number and min/max for output value range
    RotaryControl(uint8_t pclk, uint8_t pdt, int min, int max);
    /// construct with pin number, min/max for output value range and click to pulse ratio
    RotaryControl(uint8_t pclk, uint8_t pdt, int min, int max, byte cpr);
    /// set output value range
    void setMinMax(int min, int max);
    void setStep(int st);
    int getStep();
    void setRoundToStep(bool rts);
    bool getRoundToStep();

    /// set current value
    void setValue(int val);
    /// get current value
    int getValue();
    /// update the control and check for changes, usually called from main loop()
    void loop();

    /// set a handler for value changes, the optional id will be passed to the callback
    void setChangeHandler(RotaryChangeCallback fptr);
    void setChangeHandler(RotaryChangeCallback fptr, byte id);
private:
    uint8_t pinClk;
    uint8_t pinDt;
    int prevClk{0};
    int value{0};
    int minValue{0};
    int maxValue{255};
    int step{1};
    bool roundToStep{false};
    // pulses per click, depending on hardware
    byte clickPulseRatio{2};
    RotaryChangeCallback _changeCallback = nullptr;
    byte _callbackId{0};
};


#endif //UI_ROTARYCONTROL_H
