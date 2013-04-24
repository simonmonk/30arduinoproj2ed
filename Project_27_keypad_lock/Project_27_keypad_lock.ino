// Project 27 Keypad door lock

#include <Keypad.h>
#include <EEPROM.h>

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
int solenoidPin = 10;

void setup()                    
{
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(solenoidPin, OUTPUT);
  loadCode();
  flash();
  lock();
  Serial.begin(9600);
  while(!Serial);
  Serial.print("Code is: "); Serial.println(secretCode);
  Serial.println("Change code: cNNNN");
  Serial.println("Unloack: u");
  Serial.println("Lock: l");
}

void loop()                    
{
  if (Serial.available())
  {
    char c = Serial.read();
    if (c == 'u')
    {
      unlock();
    }
    if (c == 'l')
    {
      lock();
    }
    if (c == 'c')
    {
      getNewCode();
    }
  }
  char key = keypad.getKey();
  if (key == '#')
  {
    lock();
  }
  if (key == secretCode[position])
  {
    position ++;
  }
  else if (key != 0)
  {
    lock();
  }
  if (position == 4)
  {
    unlock();
  }
  delay(100);
}

void lock()
{
  position = 0;
  digitalWrite(redPin, HIGH);
  digitalWrite(greenPin, LOW);  
  digitalWrite(solenoidPin, LOW);
  Serial.println("LOCKED");
}

void unlock()
{
  digitalWrite(redPin, LOW);
  digitalWrite(greenPin, HIGH);  
  digitalWrite(solenoidPin, HIGH);
  Serial.println("UN-LOCKED");
  delay(5000);
  lock();
}


void getNewCode()
{
  for (int i = 0; i < 4; i++ )
  {
    char ch = Serial.read();
    secretCode[i] = ch;
  }
  saveCode();
  flash();flash();
  Serial.print("Code changed to: "); Serial.println(secretCode);
}

void loadCode()
{
  if (EEPROM.read(0) == 1)
  {
    secretCode[0] = EEPROM.read(1);
    secretCode[1] = EEPROM.read(2);
    secretCode[2] = EEPROM.read(3);
    secretCode[3] = EEPROM.read(4);
  }
}

void saveCode()
{
  EEPROM.write(1, secretCode[0]);
  EEPROM.write(2, secretCode[1]);
  EEPROM.write(3, secretCode[2]);
  EEPROM.write(4, secretCode[3]);
  EEPROM.write(0, 1);  
}

void flash()
{
    digitalWrite(redPin, HIGH);
    digitalWrite(greenPin, HIGH);    
    delay(500);
    digitalWrite(redPin, LOW);
    digitalWrite(greenPin, LOW);    
}
