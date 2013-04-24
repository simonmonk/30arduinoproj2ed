int ledPin = 12;
int durations[] = {200, 200, 200, 500, 500, 500, 200, 200, 200};

void setup()                    // run once, when the sketch starts
{
  pinMode(ledPin, OUTPUT);      // sets the digital pin as output
}

void loop()                     // run over and over again
{
  for (int i = 0; i < 9; i++)
  {
    flash(durations[i]);
    if (i == 2)
    {
      delay(300);
    }
  }
  delay(1000);                  // wait 1 second before we start again
}

void flash(int duration)
{
  digitalWrite(ledPin, HIGH);
  delay(duration);           
  digitalWrite(ledPin, LOW);    
  delay(duration);
}
