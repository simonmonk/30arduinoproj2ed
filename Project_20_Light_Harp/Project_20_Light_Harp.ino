// Project 20 Light Harp

int soundPin = 11;
int pitchInputPin = 0;
int volumeInputPin = 1;
int ldrDim = 400;
int ldrBright = 800;

byte sine[] = {0, 22, 44, 64, 82, 98, 111, 120, 126, 127, 
126, 120, 111, 98, 82, 64, 44, 22, 0, -22, -44, -64, -82, 
-98, -111, -120, -126, -128, -126, -120, -111, -98, -82, 
-64, -44, -22};

long lastCheckTime = millis();
int pitchDelay;
int volume;

void setup()
{
  // change PWM frequency to 63kHz
  cli(); //disable interrupts while registers are configured
  bitSet(TCCR2A, WGM20);
  bitSet(TCCR2A, WGM21); //set Timer2 to fast PWM mode (doubles PWM frequency)
  bitSet(TCCR2B, CS20);
  bitClear(TCCR2B, CS21);
  bitClear(TCCR2B, CS22);
  sei(); //enable interrupts now that registers have been set
  pinMode(soundPin, OUTPUT);
}

void loop()                    
{
  long now = millis();
  if (now > lastCheckTime + 20L)
  {
    pitchDelay = map(analogRead(pitchInputPin), ldrDim, ldrBright, 10, 30);
    volume = map(analogRead(volumeInputPin), ldrDim, ldrBright, 1, 4);
    lastCheckTime = now;
  }

  playSine(pitchDelay, volume);
}

void playSine(int period, int volume)
{
  for( int i = 0; i < 36; i++)
  {
    analogWrite(soundPin, (sine[i] / volume) + 128);
    delayMicroseconds(period);
  }
}

