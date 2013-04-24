// Project 8 - super strobe light
int ledPin = 12;

int period = 100;

char mode = 'o';  // o-off, s-strobe, w-wave

void setup()                 
{
  pinMode(ledPin, OUTPUT);
  analogWrite(ledPin, 255);
  Serial.begin(9600);
}

void loop()                    
{
  if (Serial.available())
  {
    char ch = Serial.read();
    if (ch == '0')
    {
      mode = 0;
      analogWrite(ledPin, 255);
    }
    else if (ch > '0' && ch <= '9')
    {
      setPeriod(ch);
    }
    else if (ch == 'w' || ch == 's')
    {
      mode = ch;
    }
  }
  if (mode == 'w')
  {
    waveLoop();
  }
  else if (mode == 's')
  {
    strobeLoop();
  }
}

void setPeriod(char ch)
{
 int period1to9 = 9 - (ch - '0');
 period = map(period1to9, 0, 9, 50, 500);
}

void waveLoop()
{
  static float angle = 0.0;
  angle = angle + 0.01;
  if (angle > 3.142)
  {
     angle = 0;
  }
  // analogWrite(ledPin, 255 - (int)255 * sin(angle)); // Breadboard
  analogWrite(ledPin, (int)255 * sin(angle)); // Sheild
  delay(period / 100);
}

void strobeLoop()
{
 //analogWrite(ledPin, 0); // bradboard
 analogWrite(ledPin, 255); // shield
 delay(10);
 //analogWrite(ledPin, 255); // breadboard
 analogWrite(ledPin, 0); // shield
 delay(period);
}
