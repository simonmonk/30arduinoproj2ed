// Project_33 Accelerometer Mouse

int gndPin = A2;
int xPin = 5;
int yPin = 4;
int zPin = 3;
int plusPin = A0;
int switchPin = 12;

void setup()
{
  pinMode(gndPin, OUTPUT);
  digitalWrite(gndPin, LOW);
  pinMode(plusPin, OUTPUT);
  digitalWrite(plusPin, HIGH);
  pinMode(switchPin, INPUT_PULLUP);
  pinMode(A1, INPUT); // 3V output 
  Mouse.begin();
}

void loop()
{
  int x = analogRead(xPin) - 340;
  int y = analogRead(yPin) - 340;
  // midpoint 340, 340
  if (abs(x) > 10 || abs(y) > 10)
  {
    Mouse.move(x / 30, -y / 30, 0);
  }
  if (digitalRead(switchPin) == LOW)
  {
    Mouse.click();
    delay(100);
  }
}

