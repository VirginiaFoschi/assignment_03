#include "devices/LCD.h"

LCD::LCD()
{
  lcd.init();
  lcd.backlight();
  lcd.setCursor(2, 1);
}

LCD::~LCD()
{
}

void LCD::print(String string)
{
  lcd.clear();
  lcd.print(string);
}