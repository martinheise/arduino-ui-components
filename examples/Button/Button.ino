/**
 * Example: simple button with a callback switching an LED
 */

#include <Arduino.h>
#include <UIComponents.h>

static const uint8_t btnPin = 2;
static const uint8_t ledPin = 8;

Button button{btnPin};
LedIndicator led{ledPin};

void callbackBtn(byte id) {
    Serial.print("pressed button with id ");
    Serial.print(id, DEC);
    Serial.println();

    if (button.getValue()) {
        led.setStatus(Indicator::ON);
    } else {
        led.setStatus(Indicator::OFF);
    }
}

void setup() {
    Serial.begin(115200);
    Serial.println("Started");
    // set callback
    button.setPressedHandler(callbackBtn, 1);
}

void loop() {
    button.loop();
    led.loop();
    // use button status directly without callback:
    // bool status =  button.getValue();
    // ...
}
