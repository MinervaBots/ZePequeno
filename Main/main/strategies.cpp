#include <Arduino.h>

#include "motors.h"
#include "sensors.h"
#include "strategies.h"
#include "constants.h"

int lastToSee = -1;
void (*searchStrategy)();
void (*startStrategy)();

void avoidEdge() {
  if (anyEdge()) {
    move(lastToSee, maxPWM);
    delay(delayBackEdge);
    move(lastToSee, maxPWM);
    delay(delaySpinEdge);
  }
}

void radarSearch() {
  if (anyIR()) {
    int side = readIRs();
    move(side, maxPWM);
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
    move(side, maxPWM);
    lastToSee = side;
  }
  else {
    move(0, maxStarPWM);
  }
  avoidEdge();
}

void archStartRight() {
  move(0.5, maxPWM, true);
  delay(delayArchStart);
}

void archStartLeft() {
  move(-0.5, maxPWM, true);
  delay(delayArchStart);
}

void backwardStart() {
  move(0, maxPWM, true);
  delay(delayBackStart);
}

void spinStartLeft() {
  lastToSee = -1;
}

void spinStartRight() {
  lastToSee = 1;
}

void attackStartRight() {
  //forward();
  move(0, maxPWM);
  delay(attackF1delay);
  spin(0);
  delay(attackS1delay);
  //forward();
  move(0, maxPWM);
  delay(attackF2delay);
  spin(0);
  delay(attackS2delay);
}

void attackStartLeft() {
  //forward();
  move(0, maxPWM);
  delay(attackF1delay);
  spin(1);
  delay(attackS1delay);
  //forward();
  move(0, maxPWM);
  delay(attackF2delay);
  spin(1);
  delay(attackS2delay);
}

void nothing() {
  Serial.println("nothing");
}

void verifyStartStrategy() {
  if ((not strategyButton(1)) and (not strategyButton(2)) and (not strategyButton(3))) { //000x
    startStrategy = &nothing;
    Serial.println("000");
  }
  else if ((not strategyButton(1)) and (not strategyButton(2)) and (strategyButton(3))) { //001x
    startStrategy = &backwardStart;
    Serial.println("001");
  }
  else if ((not strategyButton(1)) and (strategyButton(2)) and (not strategyButton(3))) { //010x
    startStrategy = &archStartRight;
    Serial.println("010");
  }
  else if ((not strategyButton(1)) and (strategyButton(2)) and (strategyButton(3))) { //011x
    startStrategy = &archStartLeft;
    Serial.println("011");
  }
  else if ((strategyButton(1)) and (not strategyButton(2)) and (not strategyButton(3))) { //100x
    startStrategy = &attackStartRight;
    Serial.println("100");
  }
  else if ((strategyButton(1)) and (not strategyButton(2)) and (strategyButton(3))) { //101x
    startStrategy = &attackStartLeft;
    Serial.println("101");
  }
  else if ((strategyButton(1)) and (strategyButton(2)) and (not strategyButton(3))) { //110x
    startStrategy = &spinStartLeft;
    Serial.println("110");
  }
  else //if ((strategyButton(1)) and (strategyButton(2)) and (strategyButton(3))) //111x
  {
    startStrategy = &spinStartRight;
    Serial.println("111");
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
