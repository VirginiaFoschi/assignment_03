#include "devices/Potentiometer.h"

Potentiometer::Potentiometer()
{
}

double Potentiometer::getValveOpeningLevel()
{
    int sensorValue = analogRead(PIN_POT);
    int valvePos = map(sensorValue, 0, 1023, 0, 180);
    // Arrotondamento al multiplo di 5 più vicino
    int roundedValvePos = (valvePos + 2) / 5 * 5; 
    return roundedValvePos;
}

Potentiometer::~Potentiometer()
{
}