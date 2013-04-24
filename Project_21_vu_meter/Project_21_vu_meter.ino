// Project 21 - VU Meter

int ledPins[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
int switchPin = 12;
int soundPin = 0;

boolean showPeak = false;
int peakValue = 0;

void setup()                 
{
  for (int i = 0; i < 10; i++)
  {
     pinMode(ledPins[i], OUTPUT); 
  }
  pinMode(switchPin, INPUT_PULLUP);
}

void loop()                   
{
  if (digitalRead(switchPin) == LOW)
  {
    showPeak = ! showPeak;
    peakValue = 0;
    delay(200); // debounce switch 
  }
  int value = analogRead(soundPin);
  int topLED = map(value, 0, 1023, 0, 11) - 1;
  if (topLED > peakValue)
  {
    peakValue = topLED;
  }
  for (int i = 0; i < 10; i++)
  {
      digitalWrite(ledPins[i], (i <= topLED || (showPeak && i == peakValue)));
  }
}
