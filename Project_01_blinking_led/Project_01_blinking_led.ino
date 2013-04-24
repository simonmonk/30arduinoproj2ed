
int ledPin = 12;                // LED connected to digital pin 13

void setup()                    // run once, when the sketch starts
{
  pinMode(ledPin, OUTPUT);      // sets the digital pin as output
}

void loop()                     // run over and over again
{
  digitalWrite(ledPin, HIGH);   // sets the LED on
  delay(200);                  // waits for a second
  digitalWrite(ledPin, LOW);    // sets the LED off
  delay(200);                  // waits for a second
}
