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
  return (right ? (analogRead(rightEdge)  < edgeLimit) : analogRead(leftEdge)  < edgeLimit);
}
    
bool anyEdge() {
  return (readEdge(0) || readEdge(1));
}

bool readIR(bool right) {
  return right ? (digitalReadFast(rightIR)) : (digitalReadFast(leftIR));
}

int readIRs() {
  return readIR(1) - readIR(0);
}

bool anyIR() {
  return (readIR(0) || readIR(1));
}
