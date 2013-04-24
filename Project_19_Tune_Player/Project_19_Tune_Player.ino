// Project 19 Tune Player

int soundPin = 11;

byte sine[] = {0, 22, 44, 64, 82, 98, 111, 120, 126, 127, 
126, 120, 111, 98, 82, 64, 44, 22, 0, -22, -44, -64, -82, 
-98, -111, -120, -126, -128, -126, -120, -111, -98, -82, 
-64, -44, -22};

int toneDurations[] = {120, 105, 98, 89, 78, 74, 62};  

char* song = "e e ee e e ee e g c d eeee f f f f f e e e e d d e dd gg e e ee e e ee e g c d eeee f f f f f e e e g g f d cccc";

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
  int i = 0;
  char ch = song[0];
  while (ch != 0)
  {
    if (ch == ' ')
    {
      delay(75);
    }
    else if (ch >= 'a' and ch <= 'g')
    {
      playNote(toneDurations[ch - 'a']);
    }
    i++;
    ch = song[i]; 
  }
  
  delay(5000); 
}

void playNote(int pitchDelay)
{
  long numCycles = 5000 / pitchDelay;
  for (int c = 0; c < numCycles; c++)
  {
    playSine(pitchDelay);
  }
}

void playSine(int period)
{
  for( int i = 0; i < 36; i++)
  {
    analogWrite(soundPin, sine[i] + 128);
    delayMicroseconds(period);
  }
}
