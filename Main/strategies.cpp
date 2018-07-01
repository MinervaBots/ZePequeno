#include <Arduino.h>
#include "motors.h"
#include "sensors.h"
#include "strategies.h"
#include "const.h"

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
    if (boardSide == 0)
    {
      unsigned long startTime = millis();
      while (millis() - startTime < delayBackEdge * 1.5) // delay(delayBackEdge*1.5);
      {
      }
      moveLooking(delaySpinEdge * 1.2, maxPWM , -lastEdgeSide);
    }
    else
    {

      unsigned long startTime = millis();
      while (millis() - startTime < delayBackEdge) //delay(delayBackEdge);
      {
      }
      moveLooking(delaySpinEdge, maxPWM * 1.3, -boardSide);
      lastEdgeSide = boardSide;
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
      move(side , maxPWM * 0.3);
      //Serial.println("Motor pro lado 1");
    }
    lastToSee = side;
  }
  else
  {
    move(lastToSee, maxPWM * 0.4);
    //Serial.println("Motor pro lado 2");
  }
  
  avoidEdge();
}

void starSearch()
{
  //Serial.println("Inicio do loop");
  avoidEdge();
  int side;

  float dir = readIR();
  if(abs(dir) > 0.8)
  {
    move(dir/abs(dir), maxPWM);
  }
  else
  {
    move(dir, maxPWM);
  }
  /*
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
    Serial.println("Ta indo pra frente");
    move(0, maxStarPWM);
  }
  //Serial.println("Final do loop");
  */
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
  move(-leftDibreAngular, leftFlankPWM, true);
  delay(leftDibreDelay);
}

void rightDibre()
{
  move(rightDibreAngular, leftFlankPWM, true);
  delay(rightDibreDelay);
}

void x() {
  int t = 1000;
  int start = time();
  forward();
  while (time() - start < t) {
    se só o da esquerda ve {
      lastToSee = esquerda
    se só o da direita ve {
      lastToSee = direita
    }
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
    //Serial.println("001");
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
    startStrategy = &attackStartLeft;
    //Serial.println("101");
  }/*
  else if ((strategyButton(1)) and (strategyButton(2)) and (not strategyButton(3)))      //110x
  { 
    //startStrategy = &spinStartLeft;
    //Serial.println("110");
  }/*
  else //if ((strategyButton(1)) and (strategyButton(2)) and (strategyButton(3)))        //111x
  {
    //startStrategy = &spinStartRight;
    //Serial.println("111");
  }*/
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
