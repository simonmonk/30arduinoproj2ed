
// Project 30 - Countdown Timer

#include <Adafruit_LEDBackpack.h>
#include <Adafruit_GFX.h>
#include <Wire.h>

Adafruit_7segment display = Adafruit_7segment();

int times[] = {5, 10, 15, 20, 30, 45, 100, 130, 200, 230, 300, 400, 500, 600, 700, 800, 900, 1000, 1500, 2000, 3000};
int numTimes = 19;

int buzzerPin = 11;
int aPin = 2;
int bPin = 4;
int buttonPin = 3;

boolean stopped = true;

int selectedTimeIndex = 12;
int timerMinute;
int timerSecond;
   
void setup()
{
  pinMode(buzzerPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(aPin, INPUT_PULLUP);  
  pinMode(bPin, INPUT_PULLUP);
  Serial.begin(9600);
  display.begin(0x70);
  reset();
}

void loop()
{
  updateCountingTime();
  updateDisplay();
  if (timerMinute == 0 && timerSecond == 0 && ! stopped)
  {
    tone(buzzerPin, 400); 
  }
  else
  {
    noTone(buzzerPin);
  }
  if (digitalRead(buttonPin) == LOW)
  {
    stopped = ! stopped;
    while (digitalRead(buttonPin) == LOW);
  }
  int change = getEncoderTurn();
  if (change != 0)
  {
    changeSetTime(change);
  }
}

void reset()
{
    timerMinute = times[selectedTimeIndex] / 100;
    timerSecond = times[selectedTimeIndex] % 100;
    stopped = true; 
    noTone(buzzerPin);
}

void updateDisplay() // mmss
{
  // update I2C display
  int timeRemaining =  timerMinute * 100 + timerSecond;
  display.print(timeRemaining, DEC);
  display.writeDisplay();
}

void updateCountingTime()
{
   if (stopped) return;
  
   static unsigned long lastMillis;
   unsigned long m = millis();
   if (m > (lastMillis + 1000) && (timerSecond > 0 || timerMinute > 0))
   {
    if (timerSecond == 0)
    { 
       timerSecond = 59;
       timerMinute --;
    }
    else
    {
       timerSecond --; 
    }
    lastMillis = m;
  }
}


void changeSetTime(int change)
{
   selectedTimeIndex += change;
   if (selectedTimeIndex < 0)
   {
     selectedTimeIndex = numTimes;
   }
   else if (selectedTimeIndex > numTimes)
   {
     selectedTimeIndex = 0;
   }
   timerMinute = times[selectedTimeIndex] / 100;
   timerSecond = times[selectedTimeIndex] % 100;
}


int getEncoderTurn()
{
  // return -1, 0, or +1
  static int oldA = LOW;
  static int oldB = LOW;
  int result = 0;
  int newA = digitalRead(aPin);
  int newB = digitalRead(bPin);
  if (newA != oldA || newB != oldB)
  {
    // something has changed
    if (oldA == LOW && newA == HIGH)
    {
      result = -(oldB * 2 - 1);
    }
  }
  oldA = newA;
  oldB = newB;
  return result;
} 

