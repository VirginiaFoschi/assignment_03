#include "tasks/WccsTask.h"

volatile bool pressed = false;

void pressButton()
{
    pressed = true;
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
}

void WccsTask::tick()
{
    switch (state)
    {
    case AUTOMATIC:
    {
        Serial.println("Auto");
        if (pressed)
        {
            Serial.println("Premuto");
            state = MANUAL;
            pressed = false;
        }
    }
    break;
    case MANUAL:
    {
        if (pressed)
        {
            Serial.println("Premuto MANUALE");
            state = AUTOMATIC;
            pressed = false;
        }
        else
        {
            int value = this->container->getPotentiometer()->getValveOpeningLevel();
            this->container->setNextPosValve(value);
            Serial.println("MANUALE");
        }
    }
    break;
    }
}