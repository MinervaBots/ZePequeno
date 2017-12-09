#include <Arduino.h>
#include "constants.h"
#include "motors.h"
#include "sensors.h"

#ifndef STRATEGIES_H
#define STRATEGIES_H

void starSearch();          // xxx1
void radarSearch();         // xxx0

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
  if ((not strategyButton(1)) and (not strategyButton(2)) and (not strategyButton(3))) { //000x
    startStrategy = &nothing;
  }
  if ((not strategyButton(1)) and (not strategyButton(2)) and (strategyButton(3))) { //001x
    startStrategy = &backwardStart;
  }
  if ((not strategyButton(1)) and (strategyButton(2)) and (not strategyButton(3))) { //010x
    startStrategy = &archStartRight;
  }
  if ((not strategyButton(1)) and (strategyButton(2)) and (strategyButton(3))) { //011x
    startStrategy = &archStartLeft;
  }
  if ((strategyButton(1)) and (not strategyButton(2)) and (not strategyButton(3))) { //100x
    startStrategy = &attackStartRight;
  }
  if ((strategyButton(1)) and (not strategyButton(2)) and (strategyButton(3))) { //101x
    startStrategy = &attackStartLeft;
  }
  if ((strategyButton(1)) and (strategyButton(2)) and (not strategyButton(3))) { //110x
    startStrategy = &spinStartLeft;
  }
  if ((strategyButton(1)) and (strategyButton(2)) and (strategyButton(3))) { //111x
    startStrategy = &spinStartRight;
  }
}
  
void verifySearchStrategy() {
  /*if (strategyButton(4)) { //xxx1
    searchStrategy = &radarSearch;
  }
  else { //xxx0
    searchStrategy = &starSearch;
  }
  */
  searchStrategy = &radarSearch;
}

void radarSearch() {
  if (anyIR()) {
    int side = readIRs();
    move(1, side);
    lastToSee = side;
    //Serial.println(side);  
  }
  else {
    if (lastToSee == -1) {
      spin(false);
    }
    else {
      spin(true);
    }
  }
  avoidEdge();
}

void starSearch() {
  if (anyIR()) {
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
  
void spinStartRight() {
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
