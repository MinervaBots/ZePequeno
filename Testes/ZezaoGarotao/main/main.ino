#include "constants.h"
#include "startStop.h"
#include "strategies.h"
#include "motors.h"

void setup() {
  Serial.begin(9600);
  //while(!Serial);
  
  initialSet(); // constants.h
  verifyStartStrategy(); // strategies.h
  verifySearchStrategy(); // strategies.h
  waitIR(); // startStop.h
  digitalWrite(led, LOW);
  //waitBluetooth(); // startStop.h
  delay(5000);
  digitalWrite(led, HIGH);
  startStrategy(); // strategies.h
}

void loop() {
  verifyToStopIR(); // startStop.h
  //move(0,30); 
  searchStrategy(); // strategies.h
}

void initialSet() {
  //bluetooth.begin(9600);
  button1.begin();

  pinMode(LED_BUILTIN, OUTPUT);
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
  irrecv.enableIRIn();  //começa a receber
  
  digitalWrite(led, HIGH);
}
