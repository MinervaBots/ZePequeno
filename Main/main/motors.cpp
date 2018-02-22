#include <Arduino.h>
#include "motors.h"
#include "constants.h"
 
void move(float angular, int maxPwm, bool reverse)
{
  float linear = (1 - abs(angular));
  if(reverse)
  {
    linear = -linear;
  }
  
  float leftSpeed = (linear + angular);
  float rightSpeed  = (linear - angular);

  int leftPWM = map(leftSpeed, -1, 1, -maxPwm, maxPwm);//s + 1.55*s * leftSpeed;
  int rightPWM = map(rightSpeed, -1, 1, -maxPwm, maxPwm);//s + 1.55*s * rightSpeed;

  rightPWM = abs(constrain(rightPWM, -maxPwm, maxPwm));
  leftPWM = abs(constrain(leftPWM, -maxPwm, maxPwm));

  bool rightForward = rightPWM > 0;
  bool leftForward = leftPWM > 0;
    
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
/*
void forward() {
  move(forwardSpeed,0);
  forwardSpeed = max(1, forwardSpeed + accelerationRate);
}
void backwards() {
  move(-1,0);
  forwardSpeed = 0;
}
/*
void spin(bool right) {
  if (right) {
    move(0,1);
  }
  else {
    move(0,-1);
  }
  forwardSpeed = 0;
}
*/

void spin(bool right) {
  digitalWrite(rightWheelP1, not right);
  digitalWrite(rightWheelP2, right);
  digitalWrite(leftWheelP1, not right);
  digitalWrite(leftWheelP2, right);
  analogWrite(rightWheelPWM, maxPWM);
  analogWrite(leftWheelPWM, maxPWM);
}
