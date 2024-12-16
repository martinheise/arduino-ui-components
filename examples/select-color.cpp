/**
 * Example: three controls setting the color of an RGB indicator
 */

#include <Arduino.h>
#include <UIComponents.h>

// three controls on analog input pins
Control controls[3]{
        {A0, 0, 255},
        {A1, 0, 255},
        {A2, 0, 255}
};
// RGB indicator on three output pins
RGBLedIndicator rgb{9,10,11};
// variable for our color
RGBLedIndicator::rgbColor color{0,0,0};


void updateColor() {
    color.r = controls[0].getValue();
    color.g = controls[1].getValue();
    color.b = controls[2].getValue();
    rgb.setColor(color);
}

void setup() {
    rgb.setStatus(Indicator::ON);
    updateColor();
}

void loop() {
    for (auto & control : controls) {
        control.loop();
    }
    updateColor();
    rgb.loop();
}
