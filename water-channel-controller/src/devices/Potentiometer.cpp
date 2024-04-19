#include "devices/Potentiometer.h"

Potentiometer::Potentiometer()
{
}

double Potentiometer::getValveOpeningLevel()
{
    int sensorValue = analogRead(PIN_POT);
    int valvePos = map(sensorValue, 0, 1023, 0, 180);
    return valvePos;
}

Potentiometer::~Potentiometer()
{
}