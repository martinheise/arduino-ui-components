/**
 * Example: demonstrating possibilities of LED indicators
 * and setting different configuration options
 */

#include <Arduino.h>
#include <UIComponents.h>

static const uint8_t btnPin = 2;
static const uint8_t ledPin = 8;

Button button{btnPin};
LedIndicator led{ledPin};

/**
 * button pressed: cycle through LED states
 */
void callbackBtn(byte id) {
    Serial.print("pressed button with id ");
    Serial.print(id, DEC);
    Serial.println();

    switch (led.getStatus()) {
        case Indicator::OFF:
            led.setStatus(Indicator::ON);
            break;
        case Indicator::ON:
            led.setStatus(Indicator::BLINK);
            break;
        case Indicator::BLINK:
            led.setStatus(Indicator::FAST_BLINK);
            break;
        default:
            led.setStatus(Indicator::OFF);
    }
}

/**
 * button pressed long: notification blink of LED
 * @param id
 */
void callbackBtnLong(byte id) {
    Serial.print("long pressed button with id ");
    Serial.print(id, DEC);
    Serial.println();
    led.notificationBlink();
}

void setup() {
    Serial.begin(115200);
    Serial.println("Started");
    // set callbacks
    button.setPressedHandler(callbackBtn, 1);
    button.setLongPressedHandler(callbackBtnLong, 1);
    // increased debounce time
    Button::debounceTime = 10;
    // duration until "long" handler is triggered
    Button::longPressTime = 3000;
    // speed of blinking modes (on and off duration)
    Indicator::blinkOnTime = 800;
    Indicator::blinkOffTime = 200;
    Indicator::fastBlinkOnTime = 50;
    Indicator::fastBlinkOffTime = 200;
    // duration for notification blink, until state is reverted
    Indicator::notificationBlinkTime = 5000;
}

void loop() {
    button.loop();
    led.loop();
}
