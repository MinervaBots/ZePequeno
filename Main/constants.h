#include <Arduino.h>

#ifndef CONSTANTS_H
#define CONSTANTS_H

#define led 0
#define leftWheelPWM 20
#define rightWheelPWM 21
#define leftWheelP1 15
#define leftWheelP2 14
#define rightWheelP1 18
#define rightWheelP2 19
#define leftIR 10
#define rightIR 9
#define button 5
#define leftEdge 16
#define rightEdge 17

#define accelerationRate 1 // test
#define edgeLimit 600 // test
#define maxPWM 200 // test
#define delayBackEdge 50 // test
#define delaySpinEdge 50 // test
#define attackF1delay 50 // test
#define attackF2delay 50 // test
#define attackS1delay 50 // test
#define attackS2delay 50 // test

#define SWITCH_ONE             4
#define SWITCH_TWO             3
#define SWITCH_THREE           2
#define SWITCH_FOUR            1

int forwardSpeed = 0;

void initialSet() {
  pinMode(led, OUTPUT);
  pinMode(leftWheelPWM, OUTPUT);
  pinMode(rightWheelPWM, OUTPUT);
  pinMode(leftWheelP1, OUTPUT);
  pinMode(rightWheelP1, OUTPUT);
  pinMode(leftWheelP2, OUTPUT);
  pinMode(rightWheelP2, OUTPUT);
  pinMode(leftIR, INPUT);
  pinMode(rightIR, INPUT);
  pinMode(leftEdge, INPUT);
  pinMode(rightEdge, INPUT);
  pinMode(button, INPUT);
  pinMode(SWITCH_ONE, INPUT);
  pinMode(SWITCH_TWO, INPUT);
  pinMode(SWITCH_THREE, INPUT);
  pinMode(SWITCH_FOUR, INPUT);
  
  digitalWrite(led, 1);
}

#endif
