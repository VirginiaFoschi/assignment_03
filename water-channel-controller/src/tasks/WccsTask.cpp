#include "tasks/WccsTask.h"


volatile bool pressed = false;
long prevs = 0;

void pressButton()
{
    long ts = millis();
    if (ts - prevs > 1000)
    {
        prevs = ts;
        pressed = true;
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
    this->container->getLcd()->print("Automatic Mode");
}

void WccsTask::tick()
{
    switch (state)
    {
    case AUTOMATIC:
    {
        if (pressed)
        {
            this->container->getLcd()->print("Manual Mode");
            state = MANUAL;
            pressed = false;
        }
        if (this->container->isMsgReceived())
        {
            int value = (this->container->getMsg().toInt()*180)/100;
            // Arrotondamento al multiplo di 5 più vicino
            int roundedValvePos = (value + 2) / 5 * 5; 
            this->container->setNextPosValve(roundedValvePos);
        }
    }
    break;
    case MANUAL:
    {
        if (pressed)
        {
            this->container->getLcd()->print("Automatic Mode");
            state = AUTOMATIC;
            pressed = false;
        }
        else
        {
            int value = this->container->getPotentiometer()->getValveOpeningLevel();
            this->container->setNextPosValve(value);
        }
    }
    break;
    }
}