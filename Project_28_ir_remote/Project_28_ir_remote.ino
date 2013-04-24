
// Project 28 - IR Remote
#include <EEPROM.h>

#define maxMessageSize 100
#define numSlots 9

int irRxPin = 9;
int irTxPin = 3;

int currentCode = 0;
int buffer[maxMessageSize];

void setup()
{
  Serial.begin(9600);
  Serial.println("0-9 to set code memory, l - learn, s - to send");
  pinMode(irRxPin, INPUT);
  pinMode(irTxPin, OUTPUT);
  setCodeMemory(0);
}

void loop()
{
  if (Serial.available())
  {
    char ch = Serial.read();
    if (ch >= '0' && ch <= '9')
    {
      setCodeMemory(ch - '0');
    }
    else if (ch == 's')
    {
      sendIR();
    }
    else if (ch == 'l')
    {
      int codeLen = readCode();
      Serial.print("Read code length: "); Serial.println(codeLen);
      storeCode(codeLen);
    }
  }
}

void setCodeMemory(int x) 
{
  currentCode = x;
  Serial.print("Set current code memory to: ");
  Serial.println(currentCode);
}


void storeCode(int codeLen)
{
   // write the code to EEPROM, first byte is length
   int startIndex = currentCode * maxMessageSize;
   EEPROM.write(startIndex, (unsigned byte)codeLen);
   for (int i = 0; i < codeLen; i++)
   {
      EEPROM.write(startIndex + i + 1, buffer[i]); 
   }
}

void sendIR()
{
  // construct a buffer from the saved data in EEPROM and send it
  int startIndex = currentCode * maxMessageSize;
  int len = EEPROM.read(startIndex);
  Serial.print("Sending Code for memory "); Serial.print(currentCode); 
  Serial.print(" len="); Serial.println(len);
  if (len > 0 && len < maxMessageSize)
  {
    for (int i = 0; i < len; i++) 
    {
       buffer[i] = EEPROM.read(startIndex + i + 1);
    }
    sendCode(len);
  }
}

void sendCode(int n)
{
  for (int i = 0; i < 3; i++)
 {
   writeCode(n);
   delay(90);
 } 
}


int readCode()
{
  int i = 0;
  unsigned long startTime;
  unsigned long endTime;
  unsigned long lowDuration = 0;
  unsigned long highDuration = 0;
  while(digitalRead(irRxPin) == HIGH) {}; // wait for first pulse
  while(highDuration < 5000l)
  {
    // find low duration
     startTime = micros();
     while(digitalRead(irRxPin) == LOW) {};
     endTime = micros();
     lowDuration = endTime - startTime;
     if (lowDuration < 5000l)
     {
       buffer[i] = (byte)(lowDuration >> 4);
       i ++;
     }
    // find the high duration
     startTime = micros();
     while(digitalRead(irRxPin) == HIGH) {};
     endTime = micros();
     highDuration = endTime - startTime;
     if (highDuration < 5000l)
     {
       buffer[i] = (byte)(highDuration >> 4);
       i ++;
     }
  }
  return i;
}


void writeCode(int n)
{
   int state = 0;
   unsigned long duration = 0;
   int i = 0;
   while (i < n)
   {
      duration = buffer[i] << 4;
      int cycles = duration / 14;
      if ( ! (i % 2))
      {
        for (int x = 0; x < cycles; x++)
        {
          state = ! state;
          digitalWrite(irTxPin, state);
          delayMicroseconds(10);  // less than 12 to adjust for other instructions
        }
        digitalWrite(irTxPin, LOW);
      }
      else
      {
        digitalWrite(irTxPin, LOW);
        delayMicroseconds(duration);
      }
      i ++;
   }
}
