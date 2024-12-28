# UI Components for Arduino

A toolset to simplify working with physical UI elements like buttons, potentiometers and LEDs.


## General usage

1. Include the library
2. Create class instances for the desired components, with options like pin nummbers
3. Read/write the values via the object getters/setters when needed, or add callback functions to detect changes
4. Important: from your main loop call the `loop()` method of the component objects to assure updates:


## Components overview

### Button

A simple push button, connected to a digital input pin,with configurable debouncing time.

The component stores a boolean value that is toggled whenever the button is pressed.  

A callback function can be set to be called on each press event, 
an additional callback can be used when the button is kept pressed for a longer duration (configurable).  

```
// initialize with pin:
Button button{buttonPin};
...
// set a callback
void callbackBtn(byte id) {
    // do something  ...
}
button.setPressedHandler(callbackBtn, 1);
...
// directly get the current value 
bool value = button.getValue();
```

For usage also see [Button example](examples/Button/Button.ino) and [LedStates example](examples/LedStates/LedStates.ino).

### Control

A control reads an analog input value, usually from a connecter potentiometer, and provides it as value, mapped to a defined value range.

Optionally a callback function can be defined to be called on values changes.

In “pass-through mode”, changes from the input only get effective once the currently set value is crossed/touched. This is helpful when the value is also set externally and you want to avoid sudden jumps when using the control.

```
// initialize with pin, min/max values and pass-through mode:
Control control{controlPin, -100, 100, true};
...
// set a change callback
void controlValueChange(int value, byte id) {
    // do something with value ...
}
control.setChangeHandler(controlValueChange, 1);
...
// directly get the current value 
int value = control.getValue();
```

For usage also see [Control example](examples/Control/Control.ino).

### LED indicator

An LED indicator controls the state of an LED connected to a digital output pin.
Apart from basic on/off states this includes slow and fast blinking modes, a notification trigger (fast blinking that reverts to the original state after a defined time) and a single flash. 

```
// initialize with pin number
LedIndicator led{9};
...
// set different states
led.setStatus(Indicator::ON);
led.setStatus(Indicator::BLINK);
led.setStatus(Indicator::FAST_BLINK);
led.setStatus(Indicator::OFF);
...
// trigger a notification
led.notificationBlink();
...
// trigger a single short flash
led.singleFlash();

```

Timing and blinking speeds can be configured by static variables – see [LedStates example](examples/LedStates/LedStates.ino).

### RGB indicator

Using three pins for a RGB LED. Supports all the functions of `LED indicator`, adding a color property:

```
// initialize with three pin numbers
RGBLedIndicator rgb{9,10,11};
...
// set to light blue and blink:
rgb.setColor(127, 127, 255);
rgb.setStatus(Indicator::BLINK);
```

It uses the same configuration values as `LED Indicator` class.

For usage also see [SelectColor example](examples/SelectColor/SelectColor.ino).
