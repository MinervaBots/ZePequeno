#include <Arduino.h>

#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "SoftwareSerial.h"
#include "Button.h"


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
