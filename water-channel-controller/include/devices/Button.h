#ifndef __BUTTON__
#define __BUTTON__

#include <Arduino.h>

class Button
{
private:
    bool *enable;
    int pin;
    bool pressed = false;
    long lastTimeSync;

public:
    Button(int pin);
    ~Button();
};

#endif