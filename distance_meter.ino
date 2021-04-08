int trigPin = 11;
int echoPin = 12;
int LED = 8;
long duration, cm;

void setup() 
{
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() 
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
 
 
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);

  cm = (duration/2) * 0.0343;     // Divide by 29.1 or multiply by 0.0343

  if (cm < 30)
  {

    digitalWrite(LED, HIGH);

  } 

  else
  {
    digitalWrite(LED, LOW);
  }

  if (cm < 10)
  {
    for (int x=0;x<1;x++)
    {
    digitalWrite(LED,HIGH);
    delay(50);
    digitalWrite(LED,LOW);
    }
  }
  
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();

  delay(250);

}
