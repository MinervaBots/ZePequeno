/=====Inclusão das bibliotecas
#include <Arduino.h>
#include "motors.h"
#include "sensors.h"
#include "strategies.h"
#include "constants.h"

int lastToSee = -1;
int lastEdgeSide = -1;

bool edgeBool = true;
bool IRBool = true;

void (*searchStrategy)();
void (*startStrategy)();

/=====Início da função avoidEdge
void avoidEdge() 
{
  int boardSide;
  if (anyEdge(&boardSide)) {                                              // Checa se vê alguma borda
    move(0, backPWM, 1);                                                  // Vai para trás
    if(boardSide == 0)                                                    // Caso esteja vendo borda nos dois sensores..
    {
      //digitalWrite(LED_BUILTIN, HIGH);
      myDelay(delayBackEdge * 1.5);                                       // vai para trás durante um tempo (maior)
      move(lastToSee, movePWM*0.4); // Deveria ter reverse, ver isso      // depois, vira para o centro da arena, sempre checando se está vendo
      myDelay(delaySpinEdge);                                             
    }
    else                                                                  // Caso esteja vendo borda em somente um sensor..
    {
      lastEdgeSide = boardSide;
      myDelay(delayBackEdge);                                             // vai para trás durante um tempo
      move(lastToSee, movePWM*0.4);                                       // depois, vira para o centro da arena, sempre checando se está vendo
      myDelay(delaySpinEdge);
    }
  }
}

//=====Início da função radarSearch
void radarSearch()
{
  int side;
  if (anyIR(&side)) {                                                     // Checa se está vendo o inimigo, se estiver
    if (side != 0) {                                                      // Caso esteja vendo nos dois sensores..
      forward();                                                          // vai para frente
    }
    else {                                                                // Caso esteja vendo com um sensor
      move(side*0.8, maxPWM);                                             // vira para o lado do sensor que está vendo
    }
    lastToSee = side;
    //Serial.println(side);   // Debug
  }
  else {                                                                  // Se não está vendo nenhum inimigo
    move(lastToSee, maxPWM * 0.4);                                        // fica girando para o último lado que viu alguém
  }
  avoidEdge();                                                            // Função para desviar da borda
}

//=====Início da função starSearch
void starSearch() 
{
 int side;
  if (anyIR(&side)) {                                                     // Checa se está vendo algum inimigo, se estiver
    if (side == 0) {                                                      // Se estiver vendo com os dois sensores..
      forward();                                                          // vai para frente
    }
    else {                                                                // Caso esteja vendo somente com um sensor
      move(-side, 0);                                                     // fira para o lado do sensor que está vendo
    }
  }
  else {                                                                  // Caso nao esteja vendo ninguém
    move(0, maxStarPWM);                                                  // vai para frente com a velocidade da estratégia
  }
  avoidEdge();                                                            // Quando ver a borda, vira para o centro da arena
}

//=====Início da função archStartRight
void archStartRight() 
{
  move(-archAngleRight, arcPWM, true);
  myDelay(delayArchStartRight);
  move(0, maxPWM, true);                   //checar se a troca do movelooking pelo move+myDelay está ok
  myDelay(delayBackLookingRight);
}

//=====Início da função archStartLeft
void archStartLeft() 
{
  move(archAngleLeft, arcPWM, true);
  delay(delayArchStartLeft);
  move(0, maxPWM, true);                    //checar se a troca do movelooking pelo move+myDelay está ok
  myDelay(delayBackLookingLeft);
}

//=====Início da função backwardStart
void backwardStart() 
{
  move(0, maxPWM, true);
  delay(delayBackStart);
}

//=====Início da função spinStartLeft
void spinStartLeft() 
{
  lastToSee = 1;
}

//=====Início da função spinStartRight
void spinStartRight() {
  lastToSee = -1;
}

//=====Início da função attackStartRight
void attackStartRight() {
  
  move(0, maxPWM);
  myDelay(attackF1delayRight);
  
  move(lasToSee, maxPWM);
  myDelay(attackS1delayRight);
  
  move(0, maxPWM);
  myDelay(attackF1delayRight);
  
  move(lastToSee, maxPWM);
  myDelay(attackS2delayRight);
}

//=====Início da função attackStartLeft
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

//=====Início da função nothing
void nothing()
{
  //Serial.println("nothing");
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
    startStrategy = &backwardStart;
    //Serial.println("001");
  }
  else if ((not strategyButton(1)) and (strategyButton(2)) and (not strategyButton(3)))  //010x 
  { 
    startStrategy = &archStartRight;
    //Serial.println("010");
  }
  else if ((not strategyButton(1)) and (strategyButton(2)) and (strategyButton(3)))      //011x
  {
    startStrategy = &archStartLeft;
    //Serial.println("011");
  }
  else if ((strategyButton(1)) and (not strategyButton(2)) and (not strategyButton(3)))  //100x
  {
    startStrategy = &attackStartRight;
    //Serial.println("100");
  }
  else if ((strategyButton(1)) and (not strategyButton(2)) and (strategyButton(3)))      //101x
  { 
    startStrategy = &attackStartLeft;
    //Serial.println("101");
  }
  else if ((strategyButton(1)) and (strategyButton(2)) and (not strategyButton(3)))      //110x
  { 
    startStrategy = &spinStartLeft;
    //Serial.println("110");
  }
  else //if ((strategyButton(1)) and (strategyButton(2)) and (strategyButton(3)))        //111x
  {
    startStrategy = &spinStartRight;
    //Serial.println("111");
  }
}

//=====Início da função verifySearchStrategy
void verifySearchStrategy() {
  strategyButton(4) ? searchStrategy = &radarSearch : searchStrategy = &starSearch;
}
