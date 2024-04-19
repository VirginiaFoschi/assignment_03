#ifndef __LCD__
#define __LCD__

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
class LCD
{
private:
  LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 20, 4);

public:
  LCD();
  ~LCD();
  void print(String string);
};

#endif
