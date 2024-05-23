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

void LCD::print(String string, String string2)
{
  String str = string+" "+string2;
  if(this->text != str) {
    lcd.clear();
    lcd.print(string);
    lcd.setCursor(0,1);
    lcd.print(string2);
    this->text=str;
  }
}