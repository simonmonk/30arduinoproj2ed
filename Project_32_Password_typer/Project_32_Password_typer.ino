// Project 32 - Password Typer
#include <EEPROM.h>

int typeButton = 9;
int generateButton = 8;
int passwordLength = 8;

char letters[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

void setup()
{
  pinMode(typeButton, INPUT_PULLUP);
  pinMode(generateButton, INPUT_PULLUP);
  Keyboard.begin();
}

void loop()
{
  if (digitalRead(typeButton) == LOW)
  {
    typePassword();
  }
  if (digitalRead(generateButton) == LOW)
  {
    generatePassword();
  }
  delay(300);
}

void typePassword()
{
  for (int i = 0; i < passwordLength; i++)
  {
    Keyboard.write(EEPROM.read(i));
  }
  Keyboard.write('\n');
}

void generatePassword()
{
  randomSeed(millis() * analogRead(A0));
  for (int i = 0; i < passwordLength; i++)
  {
    EEPROM.write(i, randomLetter());
  }
}

char randomLetter()
{
 int n = strlen(letters);
 int i = random(n);
 return letters[i]; 
}
