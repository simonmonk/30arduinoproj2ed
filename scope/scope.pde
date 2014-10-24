import processing.serial.*;

final int dt = 5;
final int width = 800;
final int height = 600;
final int messageHeight = 30;

Serial myPort;
int reading;
int t = 0;
int a_ = 128;

void setup() 
{
  size(width, height);
  background(255, 255, 255);
  makeConnection();  
}


void draw()
{
  if (t == 0)
  {
    while (getNextReading() != 128) {}; // wait for zero crossing
  }
  int a = (256 - getNextReading()) * 2 + messageHeight;
  // clear a vertical strip just infront of waveform
  fill(255, 255, 255);
  noStroke();
  rect(t, messageHeight+1, dt, height-messageHeight);
  // draw 0V line
  fill(0, 255, 0);
  stroke(1);
  line(t, 256 + messageHeight, t+dt, 256 + messageHeight);  
  // draw the waveform line
  fill(255, 0, 0);
  stroke(2);
  line(t, a_, t+dt, a);
  t += dt;
  a_ = a;
  if (t > width) t = 0; // flyback to start
}
 
int getNextReading()
{
  try
  {
    int readAttempts = 0;
    while ( myPort.available() <  0 && readAttempts < 10000) 
    {
      readAttempts ++;
    } 
    return myPort.read();  
  }
  catch (Exception e)
  {
    makeConnection();
  }
  return 128;
}  

void makeConnection()
{
    // I know that the first port in the serial list on my mac
  // is always my  FTDI adaptor, so I open Serial.list()[0].
  // On Windows machines, this generally opens COM1.
  // Open whatever port is the one you're using.
  String portName = "None";
  try
  {
    portName = Serial.list()[0];
    myPort = new Serial(this, portName, 115200);
    notify("Port: " + portName);
  }
  catch (Exception e)
  {
    warn("Not Connected: " + portName);
  }
}

void notify(String message)
{
  fill(255, 255, 255);
  stroke(0);
  rect(0, 0, width, messageHeight);
  fill(0, 0, 255);
  text(message, 0, 20); 
}

void warn(String message)
{
  fill(255, 0, 0);
  stroke(0);
  rect(0, 0, width, messageHeight);
  fill(0, 0, 0);
  text(message, 0, 20); 
}
