#include "Container.h"
#include "MsgService.h"

Container::Container()
{
    this->lcd = new LCD();
    this->button = new Button(2);
    this->gateDevice = new Gate();
    this->potentiometer = new Potentiometer();
    MsgService.init();
}


LCD *Container::getLcd()
{
    return this->lcd;
}


Gate *Container::getGateDevice()
{
    return this->gateDevice;
}

Button *Container::getButton()
{
    return this->button;
}

Potentiometer *Container::getPotentiometer() {
    return this->potentiometer;
}

void Container::sendMessage(String msg)
{
    MsgService.sendMsg(msg);
}

bool Container::isMsgReceived()
{
    return MsgService.isMsgAvailable();
}

void Container::sendState(String state)
{
    String s = "STATE:" + state;
    MsgService.sendMsg(s);
}

String Container::getMsg()
{
    return MsgService.receiveMsg()->getContent();
}

int Container::getNextPositionValve() {
    return this->nextPosValve;
}

void Container::setNextPosValve(int pos) {
    this->nextPosValve = pos;
}