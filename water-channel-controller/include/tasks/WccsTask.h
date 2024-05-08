#ifndef __WCCSTASK__
#define __WCCSTASK__
#include "Task.h"



class WccsTask : public Task
{
private:
    Container *container;
    enum
    {
        AUTOMATIC,
        MANUAL
    } state;

public:
    WccsTask(Container *container);
    ~WccsTask();
    void init(int period);
    void tick();
};

#endif