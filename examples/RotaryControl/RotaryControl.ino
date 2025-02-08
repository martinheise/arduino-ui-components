/**
 * Example: simple rotary control with a callback printing the read value to Serial
 */

#include <Arduino.h>
#include <UIComponents.h>

static const uint8_t clkPin = 16;
static const uint8_t dtPin = 4;
static const uint8_t btnPin = 18;

// rotary control with value range –100 to 100
// click-pulse-ratio 2, depending on hardware – change to 1 if only every second click is recognized
RotaryControl rotaryControl{clkPin, dtPin, -100, 100, 2};
// rotary own button, with integrated pullup resistor
Button rotaryButton{btnPin, INVERTED_INPUT};

void controlValueChange(int value, byte id) {
    Serial.print("value change ");
    Serial.print(value);
    Serial.print(" (");
    Serial.print(id);
    Serial.println(") ");
}

void buttonPressed(byte id) {
    Serial.println("button pressed – reset to 0");
    rotaryControl.setValue(0);
}

void setup() {
    Serial.begin(115200);
    Serial.println("Started");
    // set callback
    rotaryControl.setChangeHandler(controlValueChange);
    rotaryControl.setValue(0);
    rotaryButton.setPressedHandler(buttonPressed);
}

void loop() {
    rotaryControl.loop();
    rotaryButton.loop();
    // we can directly read the value here as needed without using a callback:
    int value = rotaryControl.getValue();
    // ...
}
