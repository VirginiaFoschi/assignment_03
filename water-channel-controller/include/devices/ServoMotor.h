#ifndef __SERVOMOTOR__
#define __SERVOMOTOR__
#include <Arduino.h>
#include <ServoTimer2.h>

#define PIN_SERVO 8
#define INITIAL_POS 0
class ServoMotor
{
private:
    ServoTimer2 motor;
public:
    ServoMotor();
    ~ServoMotor();
    void on();
    void setPosition(int angle);
    void off();
};
#endif
