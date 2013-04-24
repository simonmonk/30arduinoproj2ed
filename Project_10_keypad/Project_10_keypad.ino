// Project 10

#include <Keypad.h>

char* secretCode = "1234";
int position = 0;

const byte rows = 4; 
const byte cols = 3; 
char keys[rows][cols] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};

byte rowPins[rows] = {7, 2, 3, 5}; 
byte colPins[cols] = {6, 8, 4}; 
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, rows, cols);

int redPin = 13;
int greenPin = 12;

void setup()                    
{
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  setLocked(true);  
}

void loop()                    
{
  char key = keypad.getKey();
  if (key == '*' || key == '#')
  {
    position = 0;
    setLocked(true);
  }
  if (key == secretCode[position])
  {
    position ++;
  }
  if (position == 4)
  {
    setLocked(false);
  }
  delay(100);
}

void setLocked(int locked)
{
  if (locked)
  {
    digitalWrite(redPin, HIGH);
    digitalWrite(greenPin, LOW);  
  }
  else
  {
    digitalWrite(redPin, LOW);
    digitalWrite(greenPin, HIGH);      
  }
}
