// Project 18 - Oscilloscope

int analogPin = 0;

void setup()                 
{
 Serial.begin(115200);
}

void loop()                   
{
  int value = analogRead(analogPin);
  byte data = (value >> 2);
  Serial.write(data);
}
