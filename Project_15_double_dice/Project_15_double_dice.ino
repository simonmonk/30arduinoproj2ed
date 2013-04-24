// Project 14 - Double Dice

int segmentPins[] = {3, 2, A5, A2, A4, 4, 5, A3}; 
int displayPins[] = {A1, 6};

int buttonPin = A0;

byte digits[10][8] = {
//  a  b  c  d  e  f  g  .
  { 1, 1, 1, 1, 1, 1, 0, 0},  // 0
  { 0, 1, 1, 0, 0, 0, 0, 0},  // 1
  { 1, 1, 0, 1, 1, 0, 1, 0},  // 2
  { 1, 1, 1, 1, 0, 0, 1, 0},  // 3
  { 0, 1, 1, 0, 0, 1, 1, 0},  // 4
  { 1, 0, 1, 1, 0, 1, 1, 0},  // 5
  { 1, 0, 1, 1, 1, 1, 1, 0},  // 6
  { 1, 1, 1, 0, 0, 0, 0, 0},  // 7
  { 1, 1, 1, 1, 1, 1, 1, 0},  // 8  
  { 1, 1, 1, 1, 0, 1, 1, 0}  // 9  
};
   
void setup()
{
  for (int i=0; i < 8; i++)
  {
    pinMode(segmentPins[i], OUTPUT);
  }
  pinMode(displayPins[0], OUTPUT);
  pinMode(displayPins[1], OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
}

void loop()
{
  static int dice1;
  static int dice2;
  if (digitalRead(buttonPin) == LOW)
  {
    dice1 = random(1,7);
    dice2 = random(1,7);
  }
  updateDisplay(dice1, dice2);
}

void updateDisplay(int value1, int value2)
{
  digitalWrite(displayPins[0], LOW);
  digitalWrite(displayPins[1], HIGH);
  setSegments(value1);
  delay(5);
  digitalWrite(displayPins[0], HIGH);
  digitalWrite(displayPins[1], LOW);
  setSegments(value2);
  delay(5);  
}

void setSegments(int n)
{
  for (int i=0; i < 8; i++)
  {
    digitalWrite(segmentPins[i], ! digits[n][i]);
  } 
}
