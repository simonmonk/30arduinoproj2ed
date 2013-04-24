// Project 29 - Lilypad binary clock

#include <Time.h>

int hourLEDs[] = {1, 2, 3, 4}; // least sigificant bit frst
int minuteLEDs[] = {10, 9, 8, 7, 6, 5};
int secondLEDs[] = {17, 16, 15, 14, 13, 12};

int loopLEDs[] = {17, 16, 15, 14, 13, 12, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};

int switchPin = 18;

void setup()       
{
  for (int i = 0; i < 4; i++)
  {
     pinMode(hourLEDs[i], OUTPUT); 
  }
  for (int i = 0; i < 6; i++)
  {
     pinMode(minuteLEDs[i], OUTPUT); 
  }
  for (int i = 0; i < 6; i++)
  {
     pinMode(secondLEDs[i], OUTPUT); 
  }
  setTime(0);
}

void loop()                     
{
  if (digitalRead(switchPin))
  {
     adjustTime(1);
  }
  else if (minute() == 0 && second() == 0)
  {
    spin(hour());
  }
  updateDisplay();
  delay(1);
}

void updateDisplay()
{
  time_t t = now();
  setOutput(hourLEDs, 4, hourFormat12(t));
  setOutput(minuteLEDs, 6, minute(t));
  setOutput(secondLEDs, 6, second(t));
}


void setOutput(int *ledArray, int numLEDs, int value)
{
    for (int i = 0; i < numLEDs; i++)
    {
     digitalWrite(ledArray[i], bitRead(value, i)); 
    }
}


void spin(int count)
{
  for (int i = 0; i < count; i++)
  {
      for (int j = 0; j < 16; j++)
      {
         digitalWrite(loopLEDs[j], HIGH);
         delay(50);
         digitalWrite(loopLEDs[j], LOW);
      }
  } 
}
