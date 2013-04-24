// Project 22 - LCD Thermostat

#include <LiquidCrystal.h>

// LiquidCrystal(rs, rw, enable, d4, d5, d6, d7) 
LiquidCrystal lcd(2, 3, 4, 9, 10, 11, 12);

int relayPin = A3;
int aPin = A4;
int bPin = A1;
int buttonPin = A2;
int analogPin = A0;

float setTemp = 20.0;
float measuredTemp;
char mode = 'C';        // can be changed to F 
boolean override = false;
float hysteresis = 0.25;

void setup()
{
  lcd.begin(2, 16);
  pinMode(relayPin, OUTPUT);  
  pinMode(aPin, INPUT_PULLUP);
  pinMode(bPin, INPUT_PULLUP);
  pinMode(buttonPin, INPUT_PULLUP);
  lcd.clear();
}

void loop()
{
  static int count = 0;
  measuredTemp = readTemp();
  if (digitalRead(buttonPin) == LOW)
  {
    override = ! override;
    updateDisplay();
    delay(500); // debounce
  }
  int change = getEncoderTurn();
  setTemp = setTemp + change * 0.1;
  if (count == 1000)
  {
    updateDisplay();
    updateOutput();
    count = 0;
  }
  count ++;
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

float readTemp()
{
  int a = analogRead(analogPin);
  float volts = a / 205.0;
  float temp = (volts - 0.5) * 100; 
  return temp;
}

void updateOutput()
{
  if (override ||  measuredTemp < setTemp - hysteresis)
  {
    digitalWrite(relayPin, HIGH);
  } 
  else if (!override && measuredTemp > setTemp + hysteresis)
  {
    digitalWrite(relayPin, LOW);     
  }
}

void updateDisplay()
{
  lcd.setCursor(0,0);
  lcd.print("Actual: ");
  lcd.print(adjustUnits(measuredTemp));
  lcd.print(" o");
  lcd.print(mode);
  lcd.print(" ");
  
  lcd.setCursor(0,1);
  if (override)
  {
    lcd.print("  OVERRIDE ON   ");
  }
  else
  {
    lcd.print("Set:    ");
    lcd.print(adjustUnits(setTemp));
    lcd.print(" o");
    lcd.print(mode);
    lcd.print(" ");
  }
}

float adjustUnits(float temp)
{
  if (mode == 'C')
  {
    return temp;
  }
  else
  {
    return (temp * 9) / 5 + 32;
  }
}
