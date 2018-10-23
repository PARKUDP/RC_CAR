#include <SoftwareSerial.h>
#include <AFMotor.h>
#include <Thread.h>
#include <ThreadController.h>

const int TrigPin = A0;
const int EchoPin = A1;
const int trig = A0;
const int echo = A1;
char BT;
long duration, distance;
SoftwareSerial mySerial(A4, A5);
AF_DCMotor motor_L(3);
AF_DCMotor motor_R(4);                                             

Thread myThread1 = Thread();
Thread myThread2 = Thread();
ThreadController controll = ThreadController();

void GO();
void BACK();
void RIGHT();
void LEFT();
void STOP();
void BT_infor();    
void Obstacle_Check();
void sonic();
void final();
void GO_RIGHT();
void GO_LEFT();
void BACK_RIGHT();
void BACK_LEFT();

void setup() 
{
  Serial.begin(9600);
  mySerial.begin(9600);
  pinMode(EchoPin, INPUT);   
  pinMode(TrigPin, OUTPUT); 
  motor_L.setSpeed(250);
  motor_L.run(RELEASE);
  motor_R.setSpeed(250);
  motor_R.run(RELEASE);
  myThread1.onRun(mode_set);
  myThread1.setInterval(0);
  controll.add(&myThread1);
  myThread2.onRun(mode);
  myThread2.setInterval(2);
  controll.add(&myThread2);
}

bool bAuto = false;

void loop()
{
  controll.run();
}
void mode()
{
  if(bAuto == true)
  {
    sonic();
  }
  if(bAuto == false)
  {
    BT_infor();
  }
}
void mode_set()
{
  if(mySerial.available())
  {
   BT = mySerial.read();
   Serial.println(BT);
  }
  if(BT == 'X')
  {
    bAuto = true;
  }
  if(BT == 'x')
  {
    bAuto = false;
  }
}
void GO()
{
  motor_L.setSpeed(250);
  motor_R.setSpeed(250);
  motor_L.run(FORWARD);
  motor_R.run(FORWARD);
}
void BACK()
{
  motor_L.setSpeed(250);
  motor_R.setSpeed(250);
  motor_L.run(BACKWARD);
  motor_R.run(BACKWARD);
}
void RIGHT()
{
  motor_L.setSpeed(250);
  motor_R.setSpeed(250);
  motor_L.run(RELEASE);
  motor_R.run(FORWARD);
}
void LEFT()
{
  motor_L.setSpeed(250);
  motor_R.setSpeed(250);
  motor_L.run(FORWARD);
  motor_R.run(RELEASE);
}
  
void STOP()
{
  motor_L.run(RELEASE);
  motor_R.run(RELEASE);
}
void GO_RIGHT()
{
  motor_L.setSpeed(250);
  motor_R.setSpeed(150);
  motor_L.run(FORWARD);
  motor_R.run(FORWARD);
}
void GO_LEFT()
{
  motor_L.setSpeed(150);
  motor_R.setSpeed(250);
  motor_L.run(FORWARD);
  motor_R.run(FORWARD);
}
void BACK_RIGHT()
{
  motor_L.setSpeed(250);
  motor_R.setSpeed(150);
  motor_L.run(BACKWARD);
  motor_R.run(BACKWARD);
}
void BACK_LEFT()
{
  motor_L.setSpeed(150);
  motor_R.setSpeed(250);
  motor_L.run(BACKWARD);
  motor_R.run(BACKWARD);
}
void BT_infor()
{
  motor_L.setSpeed(255);
  motor_R.setSpeed(255);
  if(BT == 'F')
  {
    GO();
  }
  if(BT == 'B')
  {
    BACK();
  }
  if(BT == 'L')
  {
    LEFT();
  }
  if(BT == 'R')
  {
    RIGHT();
  }
  if(BT == 'G')
  {
    GO_RIGHT();
  }
  if(BT == 'I')
  {
    GO_LEFT();
  }h               
  if(BT == 'H')
  {
    BACK_RIGHT();
  }
  if(BT == 'J')
  {
    BACK_LEFT();
  }
  if(BT == 'S')
  {
    STOP();
  }
}

void Obstacle_Check()
{  
  int val = random(2);     
  Distance_Measurement();
  
  Serial.println(distance);
  
  while(distance<170)
  {      
    if(distance<20)
    {
      BACK();
      delay(250);
      STOP();
      delay(50);      
      Distance_Measurement();
    }    
    else
    {
      if(val == 0)
      {
        RIGHT();
        delay(250);
      }
      else if(val == 1)
      {
        LEFT();
        delay(250);
      }
      Distance_Measurement();
    }
  }
}

void Distance_Measurement()
{ 
  digitalWrite(TrigPin, LOW);
  delay(2);
  digitalWrite(TrigPin, HIGH);  
  delayMicroseconds(10);
  digitalWrite(TrigPin, LOW);
  duration = pulseIn(EchoPin, HIGH);    
  distance = ((float)(340 * duration) / 1000) / 2;
  delay(5);
}

void sonic()
{
  motor_L.setSpeed(250);
  motor_R.setSpeed(250);
  GO();
  delay(100);
  Obstacle_Check();
}
