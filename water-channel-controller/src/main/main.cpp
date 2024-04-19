/*Margherita Balzoni, 
Chiara Castiglioni, 
Virginia Foschi*/

#include <Arduino.h>
#include "Container.h"
#include "Scheduler.h"
#include "tasks/ValveTask.h"

Scheduler sched;
void setup()
{
  Serial.begin(9600);
  Container *container = new Container();
  sched.init(100);
  Task *t1 = new ValveTask(container);
  t1->init(100);
  sched.addTask(t1);
  
}

void loop()
{
  sched.schedule();
}