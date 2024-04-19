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
    switch (state)
    {
    case IDLE:
    {
        int gate = this->container->getNextPositionValve();
        if (gate != this->container->getGateDevice()->getCurrentPos())
        {
            state = MOVING;
        }
    }
    break;
    case MOVING:
    {
        int gate = this->container->getNextPositionValve();
        if (this->container->getGateDevice()->move(gate))
        {
            state = IDLE;
        }
    }
    break;
    }
}