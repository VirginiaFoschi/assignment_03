#include "tasks/WccsTask.h"
#include <string.h>


volatile bool pressed = false;
long prevs = 0;

void pressButton()
{
    long ts = millis();
    if (ts - prevs > 1000)
    {
        prevs = ts;
        pressed = true;
        MsgService.sendMsg(String(-1));
    }
}

WccsTask::WccsTask(Container *container)
{
    this->container = container;
    pinMode(2, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(2), pressButton, RISING);
}
WccsTask::~WccsTask()
{
}
void WccsTask::init(int period)
{
    Task::init(period);
    this->state = AUTOMATIC;
    this->container->getLcd()->print("Automatic Mode", "0%");
}

void WccsTask::tick()
{
    switch (state)
    {
    case AUTOMATIC:
    {
        if (pressed)
        {
            state = MANUAL;
            pressed = false;
        }
        else if (this->container->isMsgReceived())
        {
            String value_percent = this->container->getMsg();
            int value = (value_percent.toInt()*180)/100;
            // Arrotondamento al multiplo di 5 più vicino
            //int roundedValvePos = (value + 2) / 5 * 5; 
            int roundedValvePos = int(value/5 + 0.5) * 5;
            this->container->setNextPosValve(roundedValvePos);
            this->container->getLcd()->print("Automatic Mode", value_percent+"%");
        }
    }
    break;
    case MANUAL:
    {
        if (pressed)
        {
            state = AUTOMATIC;
            pressed = false;
        }
        else
        {
            this->container->clearBuffer();
            int value = this->container->getPotentiometer()->getValveOpeningLevel();
            this->container->setNextPosValve(value);
            int value_percent = (value*100)/180;
            this->container->getLcd()->print("Manual Mode", String(value_percent)+"%");
            this->container->sendMessage(String(value_percent));
        }
    }
    break;
    }
}