/*Margherita Balzoni, 
Chiara Castiglioni, 
Virginia Foschi*/

#include <Arduino.h>
#include "Container.h"
#include "Scheduler.h"
#include "tasks/ValveTask.h"
#include "tasks/WccsTask.h"

Scheduler sched;
void setup()
{
  Serial.begin(9600);
  Container *container = new Container();
  sched.init(100);
  Task *t1 = new ValveTask(container);
  t1->init(100);
  sched.addTask(t1);
  Task *t2 = new WccsTask(container);
  t2->init(150);
  sched.addTask(t2);
  
}

void loop()
{
  sched.schedule();
}
