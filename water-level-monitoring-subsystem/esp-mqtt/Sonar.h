#ifndef __SONAR__
#define __SONAR__

#include "Arduino.h"

class Sonar
{
private:
    const float temperature = 20;
    const float vs = 331.45 + 0.62 * temperature;
    int echoPin;
    int trigPin;

public:
    Sonar(int trigPin, int echoPin);
    ~Sonar();
    float getDistance();
};

#endif