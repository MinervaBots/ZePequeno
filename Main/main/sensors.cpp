#include <Arduino.h>
#include "sensors.h"
#include "constants.h"

bool strategyButton(int selectionButton) {
  if (selectionButton == 1) {
    return digitalRead(SWITCH_ONE);
  }
  if (selectionButton == 2) {
    return digitalRead(SWITCH_TWO);
  }
  if (selectionButton == 3) {
    return digitalRead(SWITCH_THREE);
  }
  return digitalRead(SWITCH_FOUR);
}

bool readEdge(bool right) {
  //Serial.println(analogRead(rightEdge));
  //Serial.println(analogRead(leftEdge));
  return (right ? (analogRead(rightEdge)  < edgeLimit) : analogRead(leftEdge)  < edgeLimit);
}
    
bool anyEdge(int *boardSide) {
  //bool any = (readEdge(0) || readEdge(1));
  //any ? digitalWrite(LED_BUILTIN, HIGH) : digitalWrite(LED_BUILTIN, LOW);
  //return any;
  bool right = readEdge(0);
  bool left = readEdge(1);
  *boardSide = left - right;
  return (left || right);
}

bool readIR(bool right) {
  return right ? (digitalReadFast(rightIR)) : (digitalReadFast(leftIR));
}
/*
int readIRs() {
  return readIR(1) - readIR(0);
}
*/
bool anyIR(int *side)
{
  bool right = readIR(0);
  bool left = readIR(1);
  *side = left - right;
  return (left || right);
}
