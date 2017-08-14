#include <Arduino.h>
#include "constants.h"
#include "motors.h"
#include "sensors.h"

#ifndef STRATEGIES_H
#define STRATEGIES_H

void radar() {
  if (anyIR) {
    int side = readIRs();
    move(1, side);
    lastToSee = side;    
  }
  else {
    move(0, lastToSee);
  }
}

#endif
