// Listing. Project 6.
int ledPin = 12;
int analogPin = 0;

void setup()                 
{
  pinMode(ledPin, OUTPUT);
}

void loop()                    
{
  int period = (1023 - analogRead(analogPin)) / 2 + 25;
  digitalWrite(ledPin, HIGH);
  delay(period);           
  digitalWrite(ledPin, LOW);
  delay(period);   
}

