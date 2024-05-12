#ifndef __CONTAINER__
#define __CONTAINER__

#include "devices/LCD.h"
#include "devices/Button.h"
#include "devices/Gate.h"
#include "MsgService.h"
#include "devices/Potentiometer.h"

class Container
{
private:
    LCD *lcd;
    Button *button;
    Gate *gateDevice;
    Potentiometer *potentiometer;
    int nextPosValve = 0;
    


public:
    Container();
    LCD *getLcd();
    Button *getButton();
    Gate *getGateDevice();
    Potentiometer *getPotentiometer();
    void sendMessage(String msg);
    bool isMsgReceived();
    void sendState(String state);
    String getMsg();
    int getNextPositionValve();
    void setNextPosValve(int pos);
    void clearBuffer();

};

#endif