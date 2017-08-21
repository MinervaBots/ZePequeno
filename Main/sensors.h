#include <Arduino.h>
#include "constants.h"

#ifndef SENSORS_H
#define SENSORS_H

int lastToSee = -1;

bool readIR(bool);
int readIRs();
bool anyIR();
bool readEdge(bool);
bool anyEdge();
bool strategyButton(int);

bool strategyButton(int button) {
  if (button == 1) {
    return digitalRead(SWITCH_ONE);
  }
  if (button == 2) {
    return digitalRead(SWITCH_TWO);
  }
  if (button == 3) {
    return digitalRead(SWITCH_THREE);
  }
  return digitalRead(SWITCH_ONE);
}

bool readEdge(bool right) {
  if (right) {
    return (analogRead(rightEdge) < edgeLimit);
  return (analogRead(leftEdge) < edgeLimit);
    
bool anyEdge() {
  return (readEdge(0) || readEdge(1));

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

#endif
