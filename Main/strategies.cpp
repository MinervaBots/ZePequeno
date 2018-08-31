#include <Arduino.h>
#include "motors.h"
#include "sensors.h"
#include "strategies.h"
#include "constants.h"
#include "startStop.h"
#include <EEPROM.h>

int lastToSee = -1;
int lastEdgeSide = -1;

void (*searchStrategy)();
void (*startStrategy)();

void avoidEdge()
{
  int boardSide;
  if (anyEdge(&boardSide))
  {
    move(0, backPWM, true);
    delay(delayBackEdge);
    if (boardSide == 0)
    {
      //unsigned long startTime = millis();
      //moveLooking(delaySpinEdge * 1.2, maxPWM , -lastEdgeSide);
      move(lastEdgeSide, 255, true);
      delay(delaySpinEdge);
    }
    else
    {
      unsigned long startTime = millis();
      //moveLooking(delaySpinEdge * 1.2, maxPWM , -lastEdgeSide);
      lastEdgeSide = boardSide;
      move(lastEdgeSide, 255, true);
      delay(delaySpinEdge);
    }
  }
}

void radarSearch()
{
  int side;
  /*
  float dir = readIR();
  side = dir/abs(dir);
  if(abs(dir) > 0.8)
  {
    move(side, maxPWM);
  }
  else
  {
    move(dir, maxPWM);
  }
  lastToSee = side;
  */
  
  if (anyIR(&side))
  {
    if (side == 0)
    {
      forward();
      //Serial.println("Motor para frente");
    }
    else
    {
      move(side , maxPWM * 0.25); //Vendo com um sensor
      lastToSee = side;
      //Serial.println(lastToSee);
    }
  }
  else
  {
    move(lastToSee, maxPWM * 0.4); //Não ta vendo ngm
    //Serial.println("Motor pro lado 2");
  }
  avoidEdge();
}

void starSearch()
{
  //Serial.println("Inicio do loop");
  avoidEdge();
  int side;
  /*
  float dir = readIR();
  if(abs(dir) > 0.8)
  {
    move(dir/abs(dir), maxPWM);
  }
  else
  {
    move(dir, maxPWM);
  }
  */
  if (anyIR(&side))
  {
    if (side == 0)
    {
      //Serial.println("Viu");
      forward();
    }
    else
    {
      //Serial.println("Viu de um lado 1");
      move(side, maxPWM);
    }
  }
  else
  {
    //Serial.println("Ta indo pra frente");
    move(0, maxStarPWM);
  }
  //Serial.println("Final do loop");
}

/*
void estrela()
{
  int side;
  forward();
  if(anyIR(&side))
  {
    
  }
}
*/

void nothing()
{
  //Serial.println("nada");
}

void rightFlank()
{
  move(rightFlankAngular, rightFlankPWM, false);
  delay(rightFlankDelay);
}

void leftFlank()
{
  move(-leftFlankAngular, leftFlankPWM, false);
  delay(leftFlankDelay);
}

void leftDibre()
{
  move(1, leftFlankPWM, true);
  delay(50);
  move(0, leftFlankPWM, true);
  delay(leftDibreDelay);
  /*move(-leftDibreAngular, leftFlankPWM, true);
  delay(leftDibreDelay);
  */
}

void rightDibre()
{
  move(-1, leftFlankPWM, true);
  delay(50);
  move(0, leftFlankPWM, true);
  delay(rightDibreDelay);
  /*move(rightDibreAngular, leftFlankPWM, true);
  delay(rightDibreDelay);
  */
}

void ole() {
  int side;
  int start = millis();
  forward();
  while (millis() - start < oleDelay) {
    if (anyIR(&side))
    {
      lastToSee = side;
    }
  }
}

//=====Início da função verifyStartStrategy
void verifyStartStrategy()
{
  if ((not strategyButton(1)) and (not strategyButton(2)) and (not strategyButton(3)))  //000x
  { 
    startStrategy = &nothing;
    //Serial.println("000");
  }
  else if ((not strategyButton(1)) and (not strategyButton(2)) and (strategyButton(3)))  //001x
  {
    startStrategy = &rightFlank;
    //Serial.println("001");+
  }
  else if ((not strategyButton(1)) and (strategyButton(2)) and (not strategyButton(3)))  //010x 
  { 
    startStrategy = &leftFlank;
    //Serial.println("010");
  }
  else if ((not strategyButton(1)) and (strategyButton(2)) and (strategyButton(3)))      //011x
  {
    startStrategy = &leftDibre;
    //Serial.println("011");
  }
  else if ((strategyButton(1)) and (not strategyButton(2)) and (not strategyButton(3)))  //100x
  {
    startStrategy = &rightDibre;
    //Serial.println("100");
  }
  else if ((strategyButton(1)) and (not strategyButton(2)) and (strategyButton(3)))      //101x
  { 
    startStrategy = &ole;
    //Serial.println("101");
  }/*
  else if ((strategyButton(1)) and (strategyButton(2)) and (not strategyButton(3)))      //110x
  { 
    //startStrategy = &spinStartLeft;
    //Serial.println("110");
  }*/
  else if ((strategyButton(1)) and (strategyButton(2)) and (strategyButton(3)))
  {
    delay(500);
    while(true) {
      calibrateSensors();
      //Serial.println(*leftSensor.calibratedMaximumOn);
      if (button1.isPressed()) {
        break;
      }
    }
    digitalWrite(led, LOW);
    putCalibration(*leftSensor.calibratedMinimumOn, *leftSensor.calibratedMaximumOn, *rightSensor.calibratedMinimumOn, *rightSensor.calibratedMaximumOn);
    while(true){}
  }
  getCalibration();
}

//=====Início da função verifySearchStrategy
void verifySearchStrategy() {
  if (strategyButton(4))
  {
    searchStrategy = &radarSearch;
  }
  else if(!strategyButton(4))
  {
    searchStrategy = &starSearch;
  }
}

void  getCalibration() {
  int leftMin, leftMax, rightMin, rightMax;
  EEPROM.get(0, leftMin);
  EEPROM.get(sizeof(int), leftMax);
  EEPROM.get(2*sizeof(int), rightMin);
  EEPROM.get(3*sizeof(int), rightMax);
  calibrateSensors();
  *leftSensor.calibratedMinimumOn = leftMin;
  *leftSensor.calibratedMaximumOn = leftMax;
  *rightSensor.calibratedMinimumOn = rightMin;
  *rightSensor.calibratedMaximumOn = rightMax;
  /*
  Serial.print(leftMin);
  Serial.print("          ");
  Serial.println(leftMax);
  Serial.print(rightMin);
  Serial.print("          ");
  Serial.print(rightMax);
  */
}

void  putCalibration(int leftMin, int leftMax, int rightMin, int rightMax) {
  EEPROM.put(0, leftMin);
  EEPROM.put(sizeof(int), leftMax);
  EEPROM.put(2*sizeof(int), rightMin);
  EEPROM.put(3*sizeof(int), rightMax);
}
