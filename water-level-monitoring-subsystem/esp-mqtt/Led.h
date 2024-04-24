#ifndef __LED__
#define __LED__

#include <Arduino.h>
class Led
{
private:
    int led_pin;

public:
    Led(int led);
    ~Led();
    void turnOn();
    void turnOff();
};
#endif