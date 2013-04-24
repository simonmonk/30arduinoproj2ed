// Listing. Project 7.

int ledPin = 11;
int analogPin = A2;

int startupSeconds = 20;
int turnOffSeconds = 10;
int minOnSeconds = 300;
int maxOnSeconds = 1800;

int brightness = 0;

void setup()                 
{
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH);
  pinMode(A0, OUTPUT);        // Use Analog pins 0 and 4 for
  pinMode(A4, OUTPUT);        // the variable resistor
  digitalWrite(A4, HIGH);
  int analogIn = analogRead(analogPin);
  int onTime = map(analogIn, 0, 1023, minOnSeconds, maxOnSeconds);
  turnOn();
  delay(onTime * 1000);
  turnOff();
}

void turnOn()                    
{
  brightness = 0;
  int period = startupSeconds * 1000 / 256;
  while (brightness < 255)
  {
    analogWrite(ledPin, 255 - brightness);
    delay(period);   
    brightness ++;
  }
}

void turnOff()                    
{
  int period = turnOffSeconds * 1000 / 256;
  while (brightness >= 0)
  {
    analogWrite(ledPin, 255 - brightness);
    delay(period);   
    brightness --;
  }
}

void loop()
{}

