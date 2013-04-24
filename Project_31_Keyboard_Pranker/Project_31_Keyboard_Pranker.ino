// Project 31 - Keyboard Pranker

void setup()
{
  randomSeed(analogRead(0));
  Keyboard.begin();
}

void loop()
{
  delay(random(10000) + 30000);
  Keyboard.print("\n\n\nWake up NeoWake up Neo\n");
  delay(random(3000) + 3000);
  Keyboard.print("The Matrix has you\n");
  delay(random(3000) + 3000);
  Keyboard.print("Follow the White Rabbit\n");
  delay(random(3000) + 3000);
  Keyboard.print("Knock, knock, Neo...\n");
}
