#include <LiquidCrystal_I2C.h>



/*
 * TimeRTC.pde
 * example code illustrating Time library with Real Time Clock.
 * 
 */
#include <LiquidCrystal_I2C.h>
#include <TimeLib.h>
#include <Wire.h>
#include <DS1307RTC.h>  // a basic DS1307 library that returns time as a time_t
LiquidCrystal_I2C lcd(0*27,16,2);

void setup()  
{
  Wire.begin(2,0);
  lcd.clear();
  lcd.init();
  lcd.backlight();
  lcd.home();
  lcd.print("Hello");
}

void loop(){}
 
