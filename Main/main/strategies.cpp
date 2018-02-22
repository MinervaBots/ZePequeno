#include <Arduino.h>

#include "motors.h"
#include "sensors.h"
#include "constants.h"

void (*searchStrategy)();
void (*startStrategy)();

void avoidEdge() {
  if (anyEdge()) {
    backwards();
    delay(delayBackEdge);
    move(0, lastToSee);
    delay(delaySpinEdge);
  }
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

void verifyStartStrategy() {
  if ((not strategyButton(1)) and (not strategyButton(2)) and (not strategyButton(3))) { //000x
    startStrategy = &nothing;
    //Serial.println("000");
  }
  else if ((not strategyButton(1)) and (not strategyButton(2)) and (strategyButton(3))) { //001x
    startStrategy = &backwardStart;
    //Serial.println("001");
  }
  else if ((not strategyButton(1)) and (strategyButton(2)) and (not strategyButton(3))) { //010x
    startStrategy = &archStartRight;
    //Serial.println("010");
  }
  else if ((not strategyButton(1)) and (strategyButton(2)) and (strategyButton(3))) { //011x
    startStrategy = &archStartLeft;
    //Serial.println("011");
  }
  else if ((strategyButton(1)) and (not strategyButton(2)) and (not strategyButton(3))) { //100x
    startStrategy = &attackStartRight;
    //Serial.println("100");
  }
  else if ((strategyButton(1)) and (not strategyButton(2)) and (strategyButton(3))) { //101x
    startStrategy = &attackStartLeft;
    //Serial.println("101");
  }
  else if ((strategyButton(1)) and (strategyButton(2)) and (not strategyButton(3))) { //110x
    startStrategy = &spinStartLeft;
    //Serial.println("110");
  }
  else if ((strategyButton(1)) and (strategyButton(2)) and (strategyButton(3))) { //111x
    startStrategy = &spinStartRight;
    //Serial.println("111");
  }
}

void verifySearchStrategy() {
  if (strategyButton(4)) { //xxx1
    searchStrategy = &radarSearch;
  }
  else { //xxx0
    searchStrategy = &starSearch;
  }
}
