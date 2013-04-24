
// Project 16 - LED MAtrix

#include <Wire.h>
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"

Adafruit_BicolorMatrix matrix = Adafruit_BicolorMatrix();

void setup() 
{
  matrix.begin(0x70);
}

void loop() 
{
  uint16_t color = random(4);
  int x = random(8);
  int y = random(8);
  matrix.drawPixel(x, y, color);
  matrix.writeDisplay();
  delay(2);
}
