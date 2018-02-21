#include <Arduino.h>
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
  if (right) {
    return (analogRead(rightEdge) < edgeLimit);
  }
  return (analogRead(leftEdge) < edgeLimit);
}
    
bool anyEdge() {
  return (readEdge(0) || readEdge(1));
}

bool readIR(bool right) {
  if (right) {
    return (digitalRead(rightIR));
  }
  return (digitalRead(leftIR));
}

int readIRs() {
  return readIR(1) - readIR(0);
}

bool anyIR() {
  return (readIR(0) || readIR(1));
}
