#include "Led.h"

Led::Led(int led)
{
    this->led_pin = led;
    pinMode(led_pin, OUTPUT);
}

Led::~Led()
{
    digitalWrite(led_pin, LOW);
}

void Led::turnOn()
{
    digitalWrite(led_pin, HIGH);
}

void Led::turnOff()
{
    digitalWrite(led_pin, LOW);
}