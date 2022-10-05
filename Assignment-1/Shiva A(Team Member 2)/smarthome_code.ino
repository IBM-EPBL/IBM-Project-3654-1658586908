#define echoPin 4
#define trigPin 3
int pir = 0;

int sensorPin = A0;
int sensorValue = 0;

int M11 = 8;
int M22 = 10;

long duration;
int distance;

void setup()
{
  Serial.begin(9600);
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);
  pinMode(13,OUTPUT);
  pinMode(2,INPUT);
  pinMode(M11,OUTPUT);
  pinMode(M22,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(sensorPin,INPUT); 
  pinMode(6,OUTPUT);
  pinMode(5,INPUT);
}

void loop()
{
  digitalWrite(12,HIGH);
  pir = digitalRead(2);
  if (pir == HIGH)
  {
    digitalWrite(13,HIGH);
    digitalWrite(trigPin,LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin,HIGH);
  	delayMicroseconds(10);
  	digitalWrite(trigPin,LOW);
    
    duration=pulseIn(echoPin,HIGH);
    distance=(duration*0.034/2);
    Serial.print("Distance : ");
    Serial.print(distance);
    Serial.println(" cm ");
    if(distance > 130)
    {
      digitalWrite(M11,LOW);
      digitalWrite(M22,HIGH);
      delay(3000);       
    }
    else
    {
      digitalWrite(M11,LOW);
      digitalWrite(M22,LOW);
      delay(3000); 
    }
    sensorValue = analogRead(sensorPin);
    Serial.println(sensorValue);
    if(sensorValue < 40)
    {
      digitalWrite(7,HIGH);
      delay(2);
    }
    else
    {
      digitalWrite(7,LOW);
    }
    delay(1000);
    if (digitalRead(5) == HIGH)
    {
      digitalWrite(6,HIGH);
      delay(1000);
      digitalWrite(6,LOW);
      delay(1000);
    }
    else if(digitalRead(5) == LOW)
    {
      digitalWrite(6,LOW);
      delay(50);
    }
  }
  else
  {
    digitalWrite(13,LOW);
  }
  delay(10);
}