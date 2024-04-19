#ifndef __VALVETASK__
#define __VALVETASK__
#include "Task.h"


class ValveTask : public Task
{
private:
    Container *container;
    enum
    {
        IDLE,
        MOVING
    } state;

public:
    ValveTask(Container *container);
    ~ValveTask();
    void init(int period);
    void tick();
};

#endif