#ifndef __SONAR__
#define __SONAR__

#include "Arduino.h"
#define PIN_POT A0

class Potentiometer
{
private:
   double valve;
public:
    Potentiometer();
    ~Potentiometer();
    double getValveOpeningLevel();
};

#endif