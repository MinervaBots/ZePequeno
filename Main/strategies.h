#include <Arduino.h>
#include "constants.h"
#include "motors.h"
#include "sensors.h"

#ifndef STRATEGIES_H
#define STRATEGIES_H

void radar();
void avoidEdge();

void radar() {
  if (anyIR) {
    int side = readIRs();
    move(1, side);
    lastToSee = side;    
  }
  else {
    move(0, lastToSee);
  }
  avoidEdge();
}

void avoidEdge() {
  if (anyEdge()) {
    backwards();
    delay(delayBackEdge);
    move(0, lastToSee);
    delay(delaySpinEdge);
  }
}

#endif
