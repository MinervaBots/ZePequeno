#include <Arduino.h>
#include "constants.h"
#include "motors.h"
#include "sensors.h"

#ifndef STRATEGIES_H
#define STRATEGIES_H

void radarSearch();
void starSearch();
void archSearch();
void avoidEdge();
void archStart(bool);
void backwardStart();

void radarSearch() {
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

void starSearch() {
  if (anyIR) {
    int side = readIRs();
    move(1, side);  
  }
  else {
    forward();
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

void archStart(bool right) {
  move(-1, 0.5 - (not right));
  delay(delayArchStart);
}

void backwardStart() {
  backwards();
  delay(delayBackStart);
}

#endif
