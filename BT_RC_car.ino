#include <SoftwareSerial.h>
#include <AFMotor.h>
AF_DCMotor motor_L(3);
AF_DCMotor motor_R(4);
char BT;     
int distance;
SoftwareSerial mySerial(A4, A5);

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
  if(mySerial.available())
  {
  int mode;
  Serial.println(sonic);
  BT = mySerial.read();
  Serial.println(BT);
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

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  motor_L.setSpeed(255);
  motor_L.run(RELEASE);
  motor_R.setSpeed(255);
  motor_R.run(RELEASE);

}

void loop() 
{
  BT_infor();
}
