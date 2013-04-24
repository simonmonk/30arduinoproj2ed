// Project 23 - Computer Controlled Fan
int motorPin = 11;

void setup()                 
{
  pinMode(motorPin, OUTPUT);
  analogWrite(motorPin, 0);
  Serial.begin(9600);
}

void loop()                    
{
  if (Serial.available())
  {
    char ch = Serial.read();
    if (ch >= '0' && ch <= '9')
    {
       int speed = ch - '0';
       if (speed == 0)
       {
         analogWrite(motorPin, 0);
       }
       else
       {
         analogWrite(motorPin, 150 + speed * 10);
       }
    }
  }
}

