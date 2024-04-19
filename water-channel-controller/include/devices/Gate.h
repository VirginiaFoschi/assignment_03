#ifndef __GATE__
#define __GATE__
#include "ServoMotor.h"
#define DELTA 1


class Gate
{
private:
    ServoMotor *servoMotor = new ServoMotor();
    int pos = 0;
    bool open(int position);
    bool close(int position);
public:
    Gate(/* args */){};
    ~Gate(){};
    bool move(int position);
    int getCurrentPos();
};

#endif
