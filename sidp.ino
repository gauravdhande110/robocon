#include <Servo.h>
Servo myservo;
const int trigPin = 11;
const int echoPin = 10;
int pwmL1   = 2;
int pwmL2   = 3;
int pwmR1   = 4;
int pwmR2   = 5;
int dirL1   = 6;
int dirL2   = 7;
int dirR1   = 8;
int dirR2   = 9;
int pos = 0;
int preangle = 90;
int val;
int leftdis = 0;
int rightdis = 0;
int frontdis = 0;
bool first = true;
long duration;
int distance;
void setup()
{

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(pwmL1, OUTPUT);
  pinMode(pwmL2, OUTPUT);
  pinMode(pwmR1, OUTPUT);
  pinMode(pwmR2, OUTPUT);
  pinMode(dirL1, OUTPUT);
  pinMode(dirL2, OUTPUT);
  pinMode(dirR1, OUTPUT);
  pinMode(dirR2, OUTPUT);
  myservo.attach(12);
  myservo.write(90);
  Serial.begin(9600);
  bool first = true;
  digitalWrite(dirL1, LOW);
  digitalWrite(dirL2, LOW);
  digitalWrite(dirR1, HIGH);
  digitalWrite(dirR2, HIGH);
  analogWrite(pwmL1, 0);
  analogWrite(pwmL2, 0);
  analogWrite(pwmR1, 0);
  analogWrite(pwmR2, 0);
  delay(1000);
}
int distanceRet()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  return distance;
}
void forward()
{
  analogWrite(pwmL1, 70);
  analogWrite(pwmL2, 70);
  analogWrite(pwmR1, 70);
  analogWrite(pwmR2, 70);
  digitalWrite(dirL1, HIGH);
  digitalWrite(dirL2, HIGH);
  digitalWrite(dirR1, LOW);
  digitalWrite(dirR2, LOW);
}
void right()
{

  analogWrite(pwmL1, 70);
  analogWrite(pwmL2, 70);
  analogWrite(pwmR1, 70);
  analogWrite(pwmR2, 70);
  digitalWrite(dirL1, HIGH);
  digitalWrite(dirL2, LOW);
  digitalWrite(dirR1, HIGH);
  digitalWrite(dirR2, LOW);


}
void left()
{

  analogWrite(pwmL1, 70);
  analogWrite(pwmL2, 70);
  analogWrite(pwmR1, 70);
  analogWrite(pwmR2, 70);
  digitalWrite(dirL1, LOW);
  digitalWrite(dirL2, HIGH);
  digitalWrite(dirR1, LOW);
  digitalWrite(dirR2, HIGH);
}
void wait()
{

  analogWrite(pwmL1, 0);
  analogWrite(pwmL2, 0);
  analogWrite(pwmR1, 0);
  analogWrite(pwmR2, 0);
  digitalWrite(dirL1, LOW);
  digitalWrite(dirL2, LOW);
  digitalWrite(dirR1, HIGH);
  digitalWrite(dirR2, HIGH);

}
void  ser(int a)
{

  if (preangle > a)
  {
    for (pos = preangle; pos >= a; pos--)
    {
      myservo.write(pos);
      delay(15);
    }


  }
  else
  {
    for (pos = preangle; pos <= a; pos++)
    {
      myservo.write(pos);
      delay(15);
    }
  }
  preangle = a;
}
void readdis()
{
  wait();
  ser(180);
  leftdis = distanceRet();
  ser(10);
  rightdis = distanceRet();
  ser(90);
  frontdis = distanceRet();
  if (frontdis > rightdis && frontdis > leftdis)
  {
    ser(90);
  }
  else
  {
    if (leftdis > rightdis)
    {
      ser(180);
    }
    else
    {
      ser(10);
    }
  }
}
void loop() {
  if (first == true)
  {
    readdis();
    first = false;
  }
  while (distanceRet() > 30)
  {   
    if (preangle == 90 && frontdis > 30)
    {
      ser(90);
      forward();
    }
    if (preangle == 10 && rightdis > 30)
    {
      ser(10);
      right();
    }

    if (preangle == 180 && leftdis > 30)
    {
      ser(180);
      left();
    }
  }
  wait();
  first = true;
}
