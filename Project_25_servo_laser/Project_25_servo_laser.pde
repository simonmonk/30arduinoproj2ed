#include <Servo.h> 

int laserPin = 4;
Servo servoV;  
Servo servoH;  

int x = 90;
int y = 90;
int minX = 10;
int maxX = 170;
int minY = 50;
int maxY = 130;

void setup() 
{ 
  servoH.attach(3);
  servoV.attach(2);
  pinMode(laserPin, OUTPUT);
  Serial.begin(9600);
} 

void loop() 
{ 
  char ch;
  if (Serial.available())
  {
    ch = Serial.read();
    if (ch == '0')    
    {
      digitalWrite(laserPin, LOW);
    }
    else if (ch == '1')
    {
      digitalWrite(laserPin, HIGH);
    }
    else if (ch == '-')
    {
      delay(100); 
    }
    else if (ch == 'c')
    {
      x = 90;
      y = 90;
    }
    else if (ch == 'l' || ch == 'r' || ch == 'u' || ch == 'd')
    {
      moveLaser(ch, 1); 
    }
    else if (ch == 'L' || ch == 'R' || ch == 'U' || ch == 'D')
    {
      moveLaser(ch, 5); 
    }
  }
  servoH.write(x);
  servoV.write(y);    

}
 
void moveLaser(char dir, int amount)
{
  if ((dir == 'r' || dir == 'R') && x > minX)
  {
    x = x - amount;
  }
  else if ((dir == 'l' || dir == 'L') && x < maxX)
  {
    x = x + amount;
  }
  else if ((dir == 'u' || dir == 'U') && y < maxY)
  {
    y = y + amount;
  }
  else if ((dir == 'd' || dir == 'D') && x > minY)
  {
    y = y - amount;
  }
}

