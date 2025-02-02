/**
 * Example: simple control with a callback printing the read value to Serial
 */

#include <Arduino.h>
#include <UIComponents.h>

static const uint8_t clkPin = 2;
static const uint8_t dtPin = 4;

// rotary control with value range –100 to 100
RotaryControl control{clkPin, dtPin, -100, 100};

void controlValueChange(int value, byte id, bool dir) {
    Serial.print("value change ");
    Serial.print(value);
    Serial.print(" (");
    Serial.print(id);
    Serial.print(") ");
    if (dir) {
        Serial.println("clockwise");
    } else {
        Serial.println("counterclockwise");
    }
}

void setup() {
    Serial.begin(115200);
    Serial.println("Started");
    // set callback
    control.setChangeHandler(controlValueChange);
    control.setValue(0);
}

void loop() {
    control.loop();
    // we can directly read the value here as needed without using a callback:
    int value = control.getValue();
    // ...
}
