// Project 13 - Temperature Logger
#include <EEPROM.h>

#define analogPin 1
#define gndPin A0
#define plusPin A2
#define maxReadings 1000

int lastReading = 0;

boolean loggingOn;
//long period = 300;
long period = 10000; // 10 seconds
long lastLoggingTime = 0;
char mode = 'C';

void setup()
{
   pinMode(gndPin, OUTPUT);
   pinMode(plusPin, OUTPUT);
   digitalWrite(gndPin, LOW);
   digitalWrite(plusPin, HIGH);
   
   Serial.begin(9600);
   Serial.println("Ready");
   
   lastReading = EEPROM.read(0); // First byte is reading position
   char sampleCh = (char)EEPROM.read(1);// Second is logging period '0' to'9'
   if (sampleCh > '0' && sampleCh <= '9')
   {
     setPeriod(sampleCh);
   } 
   loggingOn = true;            // start logging on turn on
}

void loop()
{
  if (Serial.available())
  {
    char ch = Serial.read();
    if (ch == 'r' || ch == 'R')
    {
      sendBackdata();
    }   
    else if (ch == 'x' || ch == 'X')
    {
      lastReading = 0; 
      EEPROM.write(0, 0);
      Serial.println("Data cleared");
    }
    else if (ch == 'g' || ch == 'G')
    {
      loggingOn = true;
      Serial.println("Logging started");
    }
    else if (ch > '0' && ch <= '9')
    {
      setPeriod(ch);
    }
    else if (ch == 'c' or ch == 'C')
    {
      Serial.println("Mode set to deg C");
      mode = 'C';
    }
    else if (ch == 'f' or ch == 'F')
    {
      Serial.println("Mode set to deg F");
      mode = 'F';
    }
    else if (ch == '?')
    {
      reportStatus();
    }
  }
  long now = millis();
  if (loggingOn && (now > lastLoggingTime + period))
  {
    logReading();
    lastLoggingTime = now;
  }
}

void sendBackdata()
{
   loggingOn = false;
   Serial.println("Logging stopped");
   Serial.println("------ cut here ---------");
   Serial.print("Time (min)\tTemp (");
   Serial.print(mode);
   Serial.println(")");
   for (int i = 0; i < lastReading + 2; i++)
   {
      Serial.print((period * i) / 60000);
      Serial.print("\t");
      float temp = getReading(i);
      if (mode == 'F')
      {
        temp = (temp * 9) / 5 + 32;
      }
      Serial.println(temp);
   }
   Serial.println("------ cut here ---------");
}

void setPeriod(char ch)
{
   EEPROM.write(1, ch);
   long periodMins = ch - '0';
   Serial.print("Sample period set to: ");
   Serial.print(periodMins);
   Serial.println(" mins");
   period = periodMins * 60000;
}

void logReading()
{
  if (lastReading < maxReadings)
  {
    storeReading(measureTemp(), lastReading);
    lastReading++;
  }
  else
  {
    Serial.println("Full! logging stopped");
    loggingOn = false; 
  }
}

float measureTemp()
{
  int a = analogRead(analogPin);
  float volts = a / 205.0;
  float temp = (volts - 0.5) * 100; 
  return temp;
}

void storeReading(float reading, int index)
{
  EEPROM.write(0, (byte)index); // store the number of samples in byte 0
  byte compressedReading = (byte)((reading + 20.0) * 4);
  EEPROM.write(index + 2, compressedReading);
  reportStatus();
}

float getReading(int index)
{
  lastReading = EEPROM.read(0);
  byte compressedReading = EEPROM.read(index + 2);
  float uncompressesReading = (compressedReading / 4.0) - 20.0;
  return uncompressesReading;
}

void reportStatus()
{
 Serial.println("----------------");
 Serial.println("Status");
 Serial.print("Current Temp C");
 Serial.println(measureTemp());
 Serial.print("Sample period (s)\t");
 Serial.println(period / 1000);
 Serial.print("Num readings\t");
 Serial.println(lastReading);
 Serial.print("Mode degrees\t");
 Serial.println(mode);
 Serial.println("----------------"); 
}
