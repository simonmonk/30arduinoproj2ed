
// Project 17 - LCD message board

#include <LiquidCrystal.h>

//LiquidCrystal(rs, rw, enable, d4, d5, d6, d7) 
LiquidCrystal lcd(2, 3, 4, 9, 10, 11, 12);


void setup()
{
  Serial.begin(9600);
  lcd.begin(2, 20);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Evil Genius");
  lcd.setCursor(0,1);
  lcd.print("Rules");
}



void loop()
{
  if (Serial.available()) 
  {
    char ch = Serial.read();
    if (ch == '#')
    {
      lcd.clear();
    }
    else if (ch == '/')
    {
      lcd.setCursor(0,1);
    }
    else
    {
      lcd.write(ch);
    }
  }
}


