#include <Arduino.h>
#include "motors.h"
#include "const.h"
#include "sensors.h"

float forwardSpeed = 0;
 
void move(float angular, int maxPwm, bool reverse) 
{
  if (angular != 0) {
    forwardSpeed = 0;
  }
  float linear = (1 - abs(angular));  
  if(reverse)
  {
    linear = -linear;
  }
  
  float leftSpeed = (linear + angular); 
  float rightSpeed  = (linear - angular); 

  int leftPWM = map(leftSpeed, -1, 1, -maxPwm, maxPwm);
  int rightPWM = map(rightSpeed, -1, 1, -maxPwm, maxPwm);

  rightPWM = abs(constrain(rightPWM, -maxPwm, maxPwm));
  leftPWM = abs(constrain(leftPWM, -maxPwm, maxPwm));
  /*
  Serial.print(leftPWM);
  Serial.print("\t");
  Serial.println(rightPWM);
  */
  bool rightForward = leftSpeed > 0;
  bool leftForward = rightSpeed > 0;
    
  digitalWrite(rightWheelP1, not rightForward);
  digitalWrite(rightWheelP2, rightForward);
  digitalWrite(leftWheelP1, leftForward);
  digitalWrite(leftWheelP2, not leftForward);
  analogWrite(rightWheelPWM, abs(rightPWM));
  analogWrite(leftWheelPWM, abs(leftPWM)); 
}

void stop()
{
  analogWrite(rightWheelPWM, 0);
  analogWrite(leftWheelPWM, 0);
}

void forwardRadar()
{
  move(0, maxPWMForward);
}

void forward() {
  move(0,forwardSpeed*PWMAcceleration);
  forwardSpeed = min(1, forwardSpeed + accelerationRate);
  //Serial.println(forwardSpeed);
}

void moveLooking(unsigned int delayToSpin, int movePWM, int lastToSee, bool reverse) {
  unsigned long tempo = millis();
  int side;
  while(millis() - tempo <= delayToSpin)
  {
    if(anyIR(&side)) 
    {
      move(side * 0.8, maxPWM);
      return;
    }
    move(lastToSee, movePWM, reverse);
  }
}

void spin(bool right) {
  digitalWrite(rightWheelP1, not right);
  digitalWrite(rightWheelP2, right);
  digitalWrite(leftWheelP1, not right);
  digitalWrite(leftWheelP2, right);
  analogWrite(rightWheelPWM, maxPWM);
  analogWrite(leftWheelPWM, maxPWM);
}
