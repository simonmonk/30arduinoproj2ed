// Project 24 - Hypnotizer

int enable1Pin = 11;
int in1Pin = 10;
int in2Pin = 9;

int speeds[] = {80, 100, 160, 240, 250, 255, 250, 240, 160, 100, 80, 
                -80, -100, -160, -240, -250, -255, -250, -240, -160, -100, -80};
int i = 0;

void setup()                
{
  pinMode(enable1Pin, OUTPUT);
  pinMode(in1Pin, OUTPUT);
  pinMode(in2Pin, OUTPUT);
}

void loop()                     
{
  int speed = speeds[i];
  i++;
  if (i == 22)
  {
    i = 0;
  }
  drive(speed);
  delay(1500);
}

void drive(int speed)
{
  if (speed > 0)
  {
    analogWrite(enable1Pin, speed);   
    digitalWrite(in1Pin, HIGH);
    digitalWrite(in2Pin, LOW);
  } 
  else if (speed < 0)
  {
    analogWrite(enable1Pin,  -speed);
    digitalWrite(in1Pin, LOW);
    digitalWrite(in2Pin, HIGH);
  }
}
