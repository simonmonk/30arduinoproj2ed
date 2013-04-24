// Project 5

#include "WProgram.h"
void setup();
void loop();
void setLights(int red, int yellow, int green);
int redPin = 2;
int yellowPin = 3;
int greenPin = 4;
int buttonPin = 5;

int state = 0;

void setup()                    
{
  pinMode(redPin, OUTPUT);    
  pinMode(yellowPin, OUTPUT);    
  pinMode(greenPin, OUTPUT);     
  pinMode(buttonPin, INPUT); 
}

void loop()                    
{
  if (digitalRead(buttonPin))
  {
    if (state == 0)
    {
      setLights(HIGH, LOW, LOW);
      state = 1;
    }
    else if (state == 1)
    {
      setLights(HIGH, HIGH, LOW);
      state = 2;
    }
    else if (state == 2)
    {
      setLights(LOW, LOW, HIGH);
      state = 3;
    }
    else if (state == 3)
    {
      setLights(LOW, HIGH, LOW);
      state = 0;
    }
    delay(1000);
  }
}

void setLights(int red, int yellow, int green)
{
  digitalWrite(redPin, red);
  digitalWrite(yellowPin, yellow);
  digitalWrite(greenPin, green);
}  
  

int main(void)
{
	init();

	setup();
    
	for (;;)
		loop();
        
	return 0;
}

