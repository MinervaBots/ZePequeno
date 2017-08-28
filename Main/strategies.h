#include <Arduino.h>
#include "constants.h"
#include "motors.h"
#include "sensors.h"

#ifndef STRATEGIES_H
#define STRATEGIES_H

void starSearch();          // xxx0
void radarSearch();         // xxx1

void nothing();             // 000x
void backwardStart();       // 001x
void archStartRight();      // 010x
void archStartLeft();       // 011x
void attackStartRight();    // 100x
void attackStartLeft();     // 101x
void spinStartLeft();       // 110x
void spinStartRight();      // 111x

void avoidEdge();

void verifyStartStrategy();
void verifySearchStrategy();

void (*searchStrategy)();
void (*startStrategy)();

void verifyStartStrategy() {
  if (not strategyButton(1)) {
    if (strategyButton(2)) {
      startStrategy = backwardStart;
    }
  else {
    if (not strategyButton(2)) {
      startStrategy = archStart;
    }
    else {
      startStrategy = surpriseAttackStart;
    }
  }
}
  
void verifySearchStrategy() {
  if strategyButton(1) {
    searchStrategy = radarSearch;
  }
  else {
    searchStrategy = starSearch;
  }
}

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
    lastToSee = side;
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

void archStartRight() {
  move(-1, 0.5);
  delay(delayArchStart);
}
  
void archStartLeft() {
  move(-1, -0.5);
  delay(delayArchStart);
}

void backwardStart() {
  backwards();
  delay(delayBackStart);
}

void spinStartLeft() {
  lastToSee = -1;
}
  
void spinStartLeft() {
  lastToSee = 1;
}

void attackStartRight() {
  forwardSpeed = 1;
  forward();
  delay(attackF1delay);
  spin(0);
  delay(attackS1delay);
  forward();
  delay(attackF2delay);
  spin(0);
  delay(attackS2delay);
}
  
void attackStartLeft() {
  forwardSpeed = 1;
  forward();
  delay(attackF1delay);
  spin(1);
  delay(attackS1delay);
  forward();
  delay(attackF2delay);
  spin(1);
  delay(attackS2delay);
}
  
void nothing() {}

#endif
