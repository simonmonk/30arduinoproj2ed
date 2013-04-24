// Project 14 - Multicolor light display

int redPin = 9;
int greenPin = 10;
int bluePin = 11;
int aPin = 2;
int bPin = 4;
int buttonPin = 3;

boolean isOn = true;
int color = 0;

long colors[48]= {
  0xFF2000, 0xFF4000, 0xFF6000, 0xFF8000, 0xFFA000, 0xFFC000, 0xFFE000, 0xFFFF00, 
  0xE0FF00, 0xC0FF00, 0xA0FF00, 0x80FF00, 0x60FF00, 0x40FF00, 0x20FF00, 0x00FF00,
  0x00FF20, 0x00FF40, 0x00FF60, 0x00FF80, 0x00FFA0, 0x00FFC0, 0x00FFE0, 0x00FFFF,
  0x00E0FF, 0x00C0FF, 0x00A0FF, 0x0080FF, 0x0060FF, 0x0040FF, 0x0020FF, 0x0000FF,
  0x2000FF, 0x4000FF, 0x6000FF, 0x8000FF, 0xA000FF, 0xC000FF, 0xE000FF, 0xFF00FF,
  0xFF00E0, 0xFF00C0, 0xFF00A0, 0xFF0080, 0xFF0060, 0xFF0040, 0xFF0020, 0xFF0000
};

void setup()
{
  pinMode(aPin, INPUT_PULLUP);
  pinMode(bPin, INPUT_PULLUP);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

void loop()
{
  if (digitalRead(buttonPin) == LOW)
  {
    isOn = ! isOn;
    delay(200);    // de-bounce
  }
  if (isOn)
  {
    int change = getEncoderTurn();
    color = color + change;
    if (color < 0)
    {
      color = 47; 
    }
    else if (color > 47)
    {
      color = 0;
    }
    setColor(colors[color]);
  }
  else
  {
   setColor(0); 
  }
}

int getEncoderTurn()
{
  // return -1, 0, or +1
  static int oldA = LOW;
  static int oldB = LOW;
  int result = 0;
  int newA = digitalRead(aPin);
  int newB = digitalRead(bPin);
  if (newA != oldA || newB != oldB)
  {
    // something has changed
    if (oldA == LOW && newA == HIGH)
    {
      result = -(oldB * 2 - 1);
    }
  }
  oldA = newA;
  oldB = newB;
  return result;
} 

void setColor(long rgb)
{
  int red = rgb >> 16;
  int green = (rgb >> 8) & 0xFF;
  int blue = rgb & 0xFF; 
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
}  
