#include <Arduino.h>

#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "SoftwareSerial.h"
#include "Button.h"

SoftwareSerial bluetooth(9, 10); // verify pins (TX,RX)

#define led 0
#define leftWheelPWM 21
#define rightWheelPWM 20
#define leftWheelP1 18
#define leftWheelP2 19
#define rightWheelP1 15
#define rightWheelP2 14
#define leftIR 10
#define rightIR 9
#define button 5
#define leftEdge 16
#define rightEdge 17

#define accelerationRate 1 // test
#define edgeLimit 600 // test
#define maxPWM 50 // test
#define delayBackStart 50 // test
#define delayArchStart 50 // test
#define delayBackEdge 50 // test
#define delaySpinEdge 50 // test
#define attackF1delay 50 // test
#define attackF2delay 50 // test
#define attackS1delay 50 // test
#define attackS2delay 50 // test

#define SWITCH_ONE             4
#define SWITCH_TWO             3 // não funcionando
#define SWITCH_THREE           2
#define SWITCH_FOUR            1

int forwardSpeed = 0;
Button button1(button);

void initialSet() {
  
  bluetooth.begin(9600);
  button1.begin();
  
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
  pinMode(SWITCH_ONE, INPUT);
  pinMode(SWITCH_TWO, INPUT);
  pinMode(SWITCH_THREE, INPUT);
  pinMode(SWITCH_FOUR, INPUT);
  
  digitalWrite(led, 1);
}

#endif
