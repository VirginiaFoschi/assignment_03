#include "devices/ServoMotor.h"

ServoMotor::ServoMotor(){
    this->on();
    this->setPosition(INITIAL_POS);
    delay(1000);
    this->off();
}

ServoMotor::~ServoMotor()
{
}

void ServoMotor::on()
{
    motor.attach(PIN_SERVO);
}

void ServoMotor::setPosition(int angle)
{
    float coeff = (2250.0-750.0)/180;
    motor.write(750 + angle*coeff);
}

void ServoMotor::off()
{
    motor.detach();
}