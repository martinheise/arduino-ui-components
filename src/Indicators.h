#ifndef UI_INDICATORS_H
#define UI_INDICATORS_H

#include "Arduino.h"

/**
 * base class for indicator, handling common logic like currStatus change and blinking
 * does not contain actual connections to output
 */
class Indicator {
public:
    /// available status codes
    enum status {
        OFF,
        ON,
        BLINK,
        FAST_BLINK
    };
    /// set the currStatus of the indicator
    void setStatus(status s);
    /// set the currStatus of the indicator
    status getStatus();
    /// blink for a short time and revert to currStatus then
    void notificationBlink();
    /// short singleFlash and revert to currStatus then
    void singleFlash();
    /// update the indicator, usually called from main loop()
    void loop();
    /// configuration: blink on time (ms)
    static unsigned int blinkOnTime;
    /// configuration: blink off time (ms)
    static unsigned int blinkOffTime;
    /// configuration: fast blink on time (ms)
    static unsigned int fastBlinkOnTime;
    /// configuration: fast blink off time (ms)
    static unsigned int fastBlinkOffTime;
    /// configuration: duration of notificationBlink (ms)
    static unsigned int notificationBlinkTime;
    /// configuration: duration of singleFlash (ms)
    static unsigned int singleFlashTime;
protected:
    status currStatus{OFF};
    virtual void switchOn();
    virtual void switchOff();
    // remember last switch state, to update only on state changes
    bool switchState{false};
    // force a one-time update regardless of switch state
    bool forceUpdate{true};
    // start time of notification blink
    unsigned long notificationBlinkStart{0};
    // start time of singleFlash
    unsigned long singleFlashStart{0};
    // static variables for global/synced currStatus
    static unsigned long blinkStart;
    static unsigned long fastBlinkStart;
};

/**
 * simple LED indicator
 * uses digitalWrite() on selected pin to switch LED on/off
 */
class LedIndicator : public Indicator {
public:
    /// construct with pin number
    LedIndicator(uint8_t p); // NOLINT(*-explicit-constructor)
private:
    void switchOn() override;
    void switchOff() override;
    uint8_t pin{0};
};

/**
 * RGB indicator
 * uses analogWrite() on three pins for color output
 */
class RGBLedIndicator : public Indicator {
public:
    /// RGB color values 0–255
    struct rgbColor {
        uint8_t r;
        uint8_t g;
        uint8_t b;
    };
    /// construct with three pin numbers for RGB output
    RGBLedIndicator(uint8_t pr, uint8_t pg, uint8_t pb);
    /// set the color
    void setColor(rgbColor c);
    void setColor(uint8_t r, uint8_t g, uint8_t b);
    /// get current color
    rgbColor getColor();
private:
    void switchOn() override;
    void switchOff() override;
    uint8_t pins[3]{0};
    rgbColor color{255, 255, 255};
};

#endif //UI_INDICATORS_H
