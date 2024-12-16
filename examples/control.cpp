/**
 * Example: simple control with a callback printing the read value to Serial
 */

#include <Arduino.h>
#include <UIComponents.h>

static const uint8_t controlPin = A0;

// control with value range –100 to 100, pass-through mode
Control control{controlPin, -100, 100, true};

void controlValueChange(int value, byte id) {
    Serial.print("value change ");
    Serial.print(value);
    Serial.print(" (");
    Serial.print(id);
    Serial.println(")");
}

void setup() {
    Serial.begin(115200);
    Serial.println("Started");
    // set callback
    control.setChangeHandler(controlValueChange);

    // with pass-through mode enabled: value will change only when value 0 (middle of pot) is crossed
    control.setValue(0);
    // increase in case min/max values are not reached
    Control::inputEdges = 5;
}

void loop() {
    control.loop();
    // we can directly read the value here as needed without using a callback:
    int value = control.getValue();
    // ...
}
