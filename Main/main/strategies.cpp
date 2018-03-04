#include <Arduino.h>

#include "motors.h"
#include "sensors.h"
#include "strategies.h"
#include "constants.h"

int lastToSee = -1;
int lastEdgeSide = -1;

void (*searchStrategy)();
void (*startStrategy)();

void avoidEdge() {
  int boardSide;
  if (anyEdge(&boardSide)) {
    move(0, backPWM, 1);
    if(boardSide == 0)
    {
      //digitalWrite(LED_BUILTIN, HIGH);
      delay(delayBackEdge * 1.5);
      moveLooking(delaySpinEdge * 1.5, maxPWM, -lastEdgeSide);
    }
    else
    {
      lastEdgeSide = boardSide;
      delay(delayBackEdge);
      moveLooking(delaySpinEdge, maxPWM, -lastEdgeSide);
    }
  }
}

void radarSearch() {
  int side;
  if (anyIR(&side)) {
    move(side*0.2, maxPWM);
    lastToSee = side;
    //Serial.println(side);
  }
  else {
    move(lastToSee, maxPWM * 0.75);
    /*
    if (lastToSee == -1) {
      spin(false);
      
    }
    else {
      spin(true);
    }
    */
  }
  avoidEdge();
}

void starSearch() {
  int side;
  if (anyIR(&side)) {
    move(side, maxPWM);
    lastToSee = side;
    
  }
  else {
    move(0, maxStarPWM);
  }
  avoidEdge();
}

void archStartRight() {
  move(-archAngleRight, arcPWM, true);
  delay(delayArchStartRight);
  moveLooking(delayBackLookingRight, maxPWM, 0, true);
}

void archStartLeft() {
  move(archAngleLeft, arcPWM, true);
  delay(delayArchStartLeft);
  moveLooking(delayBackLookingLeft, maxPWM, 0, true);
}

void backwardStart() {
  move(0, maxPWM, true);
  delay(delayBackStart);
}

void spinStartLeft() {
  lastToSee = 1;
}

void spinStartRight() {
  lastToSee = -1;
}

void attackStartRight() {
  //forward();
  //move(0, maxPWM);
  //delay(attackF1delayRight);
  moveLooking(attackF1delayRight, maxPWM, 0);
  
  //spin(1);
  //delay(attackS1delayRight);
  moveLooking(attackS1delayRight, maxPWM, lastToSee);
  
  //forward();
  //move(0, maxPWM);
  //delay(attackF2delayRight);
  moveLooking(attackF1delayRight, maxPWM);
  
  //spin(1);
  //delay(attackS2delayRight);
  moveLooking(attackS2delayRight, maxPWM, lastToSee);
}

void attackStartLeft() {
  //forward();
  move(0, maxPWM);
  delay(attackF1delayLeft);
  spin(0);
  delay(attackS1delayLeft);
  //forward();
  move(0, maxPWM);
  delay(attackF2delayLeft);
  spin(0);
  delay(attackS2delayLeft);
}

void nothing() {
  //Serial.println("nothing");
}

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
  else //if ((strategyButton(1)) and (strategyButton(2)) and (strategyButton(3))) //111x
  {
    startStrategy = &spinStartRight;
    //Serial.println("111");
  }
}

void verifySearchStrategy() {
  strategyButton(4) ? searchStrategy = &radarSearch : searchStrategy = &starSearch;
}
