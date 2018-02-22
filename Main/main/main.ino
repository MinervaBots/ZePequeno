#include "constants.h"
#include "startStop.h"
#include "strategies.h"
#include "motors.h"

void setup() {
  initialSet(); // constants.h
  verifySearchStrategy(); // strategies.h
  waitButton(); // startStop.h
  //waitBluetooth(); // startStop.h
  delay(1000);
  startStrategy(); // strategies.h
}

void loop() {
  searchStrategy(); // strategies.h
  verifyToStopButton(); // startStop.h
  //verifyToStopBluetooth(); // startStop.h
}

void initialSet() {
  Serial.begin(9600);
  //bluetooth.begin(9600);
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
  
  digitalWrite(led, HIGH);
}
