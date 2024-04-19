#include "devices/Gate.h"

bool Gate::open(int position)
{
    this->servoMotor->on();
    this->servoMotor->setPosition(this->pos);
    this->pos = this->pos - DELTA;
    delay(50);
    this->servoMotor->off();
    return this->pos == position - DELTA;
}

bool Gate::close(int position)
{
    this->servoMotor->on();
    this->servoMotor->setPosition(this->pos);
    this->pos = this->pos + DELTA;
    delay(50);
    this->servoMotor->off();
    return this->pos == position + DELTA;
}

bool Gate::move(int position)
{
    Serial.println(this->pos);
    if (this->pos < position)
    {
        return close(position);
    }
    else if (this->pos > position)
    {
        return open(position);
    }
}

int Gate::getCurrentPos() {
    return this->pos;
}