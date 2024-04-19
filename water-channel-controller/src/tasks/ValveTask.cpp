#include "tasks/ValveTask.h"

ValveTask::ValveTask(Container *container)
{
    this->container = container;
}
ValveTask::~ValveTask()
{
}
void ValveTask::init(int period)
{
    Task::init(period);
    this->state = IDLE;
}

void ValveTask::tick()
{
    int gate = this->container->getNextPositionValve();
    switch (state)
    {
    case IDLE:
    {
        if (gate != this->container->getGateDevice()->getCurrentPos())
        {
            state = MOVING;
        }
    }
    break;
    case MOVING:
    {
        if (this->container->getGateDevice()->move(gate))
        {
            state = IDLE;
        }
    }
    break;
    }
}