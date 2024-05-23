#ifndef __SCHEDULER__
#define __SCHEDULER__

#include "tasks/Task.h"

#define MAX_TASKS 50

/**
 * 
 * @author aricci
 *
 */

class Scheduler
{

  int basePeriod;
  int nTasks;
  Task *taskList[MAX_TASKS];

public:
  void init(int basePeriod);
  virtual bool addTask(Task *task);
  virtual void schedule();
};

#endif