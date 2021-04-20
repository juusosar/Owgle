#include <Servo.h>
Servo myservo;
int sensor_1_trig = 13;
int sensor_1_echo = 12;

int sensor_2_trig = 11;
int sensor_2_echo = 10;

int servo = 2;

long duration_right, duration_left, cm_right, cm_left;
int threshold = 50;
int angle = 80;


void setup() {
  Serial.begin(9600);
  myservo.attach(2);
  
  pinMode(sensor_1_trig, OUTPUT);
  pinMode(sensor_1_echo, INPUT);

  pinMode(sensor_2_trig, OUTPUT);
  pinMode(sensor_2_echo, INPUT);

}

void loop() {

  digitalWrite(sensor_1_trig, LOW);
  delayMicroseconds(5);
  digitalWrite(sensor_1_trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(sensor_1_trig, LOW);

  duration_right = pulseIn(sensor_1_echo, HIGH);

  cm_right = (duration_right/2) * 0.0343;

  Serial.print(cm_right);
  Serial.print("cm_right");
  Serial.println();

  delay(10);

  digitalWrite(sensor_2_trig, LOW);
  delayMicroseconds(5);
  digitalWrite(sensor_2_trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(sensor_2_trig, LOW);

  duration_left = pulseIn(sensor_2_echo, HIGH);

  cm_left = (duration_left/2) * 0.0343;

  Serial.print(cm_left);
  Serial.print("cm_left");
  Serial.println();


  follow();
  
  delay(10);
  
}
void follow() 
{
  if (cm_left <= threshold || cm_right <= threshold)
  {
    if (cm_left + 2 < cm_right) 
    {
      angle = angle + 2;
    }
    if (cm_right + 2 < cm_left)
    {
      angle = angle - 2;
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
