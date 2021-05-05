#include <Servo.h>
Servo myservo;
int sensor_1_trig = 13;
int sensor_1_echo = 12;

int sensor_2_trig = 11;
int sensor_2_echo = 10;

int servo = 2;

int buzzer = 9;

int on_off = 6;

int red_LED = 8;
int white_LED = 7;

long duration_right, duration_left, cm_right, cm_left;

int threshold = 50; //sets the distance on which the sensor detects 'movement'
int angle = 90; // sets the starting angle for the servo
int shout = 5; // sets the distance on which the buzzer activates
int pass; // an empty variable used in the buzz() function 


void setup() 
{
  Serial.begin(9600);
  myservo.attach(2);
  
  pinMode(sensor_1_trig, OUTPUT);
  pinMode(sensor_1_echo, INPUT);

  pinMode(sensor_2_trig, OUTPUT);
  pinMode(sensor_2_echo, INPUT);

  pinMode(buzzer, OUTPUT);

  pinMode(on_off, INPUT);

  pinMode(red_LED, OUTPUT);
  pinMode(white_LED, OUTPUT);

}

void loop() // An on/off switch controls the running of the loop. Loop consists of two sensors sending and receiving signals,
            // their signals are converted to centimeters which determine the action of the follow() and buzz() functions.
{ 
  digitalWrite(red_LED, LOW);
  digitalWrite(white_LED, LOW);
  
  if (digitalRead(on_off) == HIGH)
  {
    digitalWrite(red_LED, HIGH);
    digitalWrite(white_LED, HIGH);
    
    digitalWrite(sensor_1_trig, LOW);
    delayMicroseconds(5);
    digitalWrite(sensor_1_trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(sensor_1_trig, LOW);
  
    duration_right = pulseIn(sensor_1_echo, HIGH);
  
    cm_right = (duration_right/2) * 0.0343; //converts the distance sensor's readings to centimeters
  
    Serial.print(cm_right);
    Serial.print("cm_right");
    Serial.println();
  
    delay(5);
  
    digitalWrite(sensor_2_trig, LOW);
    delayMicroseconds(5);
    digitalWrite(sensor_2_trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(sensor_2_trig, LOW);
  
    duration_left = pulseIn(sensor_2_echo, HIGH);
  
    cm_left = (duration_left/2) * 0.0343; //converts the distance sensor's readings to centimeters
  
    Serial.print(cm_left);
    Serial.print("cm_left");
    Serial.println();
  
  
    follow();
    
    buzz();
    
    delay(5);
  
   }

}

void follow() // function which determines the servo's movement based on the sensors' readings
{
  if (cm_left <= threshold || cm_right <= threshold)
  {
    if (cm_left + 3 < cm_right) 
    {
      angle = angle + 4;
    }
    if (cm_right + 3 < cm_left)
    {
      angle = angle - 4;
    }
  }
  if (angle > 150)
  {
    angle = 150;
  }
  if (angle < 30)
  {
    angle = 30;
  }
  myservo.write(angle);
}

void buzz() // function to the owl to make a sound and turn its head away from the source if the source comes too close
{
  if (cm_right <= shout)
    if (cm_right == 0)
    {
      pass;
    } else {
      tone(buzzer, 1500);
      delay(1000);
      noTone(buzzer);
      angle = 180;
    }
      
  if (cm_left <= shout)
    if (cm_left == 0)
    {
      pass;
    } else {
      tone(buzzer, 1500);
      delay(1000);
      noTone(buzzer);
      angle = 0;
    }
}
