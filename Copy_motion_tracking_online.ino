#include <Servo.h> 
Servo myservo;        //creates servo object
const int echopin1 = 12;   //sets echopin1 @pin 10
const int trigpin1 = 13;  //sets trigpin1 @pin 11 
const int echopin2 = 10;    //sets echopin2 @pin 12
const int trigpin2 = 11;   //sets trigpin2 @pin 13
const int servo = 9;     //sets servo @pin 9 
long Rightduration, Leftduration, Rightinch, Leftinch; //establishes the variables of the duration and sets distance in inches
int threshold = 10; //Sets the sensor threshold at 10 inches
int angle = 80; //Sets the Initial angle

void setup() 
{
  myservo.attach(2); //attaches the servo on pin 2
}
void loop()
{
  pinMode(trigpin1, OUTPUT);   //trigpin1 is set as output
  digitalWrite(trigpin1, LOW);  //sets the trigpin1 to give low pulse
  delayMicroseconds(3);      //duration is 3 microseconds
  digitalWrite(trigpin1, HIGH);   //sets the trigpin1 to give high pulse
  delayMicroseconds(5);     //duration is 5 microseconds
  digitalWrite(trigpin1, LOW);  
  Rightduration = pulseIn(echopin1, HIGH); //reads high pulse
  pinMode(trigpin2, OUTPUT);  //trigpin2 is set as output 
  digitalWrite(trigpin2, LOW);  //sets the trigpin2 to give low pulse
  delayMicroseconds(3);       //duration is 3 microseconds
  digitalWrite(trigpin2, HIGH);   //sets the trigpin2 to give high pulse
  delayMicroseconds(5);       //duration is 5 microseconds
  digitalWrite(trigpin2, LOW);  
  Leftduration = pulseIn(echopin2, HIGH); //reads high pulse
  //this will convert the elapsed time into the distance
  Rightinch = microsecondsToInches(Rightduration);  
  Leftinch = microsecondsToInches(Leftduration);
  follow();   //follows the movement
}
long microsecondsToInches(long microseconds)
{ 
// The speed of sound is 340 m/s or 73.746 microseconds per inch.
// The ping travels out and back, so to find the distance of the
// object we take half of the distance traveled.
  return microseconds / 74 / 2;
}
void follow() //conditions for the follow command
{
  if (Leftinch <= threshold || Rightinch <= threshold)
  {
    if (Leftinch + 2 < Rightinch) 
    {
      angle = angle - 2;
    }
    if (Rightinch + 2 < Leftinch)
    {
      angle = angle + 2;
    }
  }
  if (angle > 160)
  {
    angle = 160;
  }
  if (angle < 0)
  {
    angle = 0;
  }
  myservo.write(angle);
}
