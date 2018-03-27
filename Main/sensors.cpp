//=====Inclusão das bibliotecas
#include <Arduino.h>
#include "sensors.h"
#include "constants.h"

volatile unsigned long delayInterrupt;

//=====Início da função strategyButton
bool strategyButton(int selectionButton) {
  if (selectionButton == 1)
  {                                    // Caso botão 1 seja selecionado, vai retornar SWITCH_ONE
    return digitalRead(SWITCH_ONE);
  }
  if (selectionButton == 2)
  {                                    // Caso botão 2 seja selecionado, vai retornar SWITCH_TWO
    return digitalRead(SWITCH_TWO);
  }
  if (selectionButton == 3) 
  {                                   // Caso botão 3 seja selecionado, vai retornar SWITCH_THREE
    return digitalRead(SWITCH_THREE);
  }
  return digitalRead(SWITCH_FOUR);  
                                      // Caso botão 4 seja selecionado, vai retornar SWITCH_FOUR
}

//=====Início da função readEdge
bool readEdge(bool right) 
{              
  return (right ? (analogRead(rightEdge)  < edgeLimit) : analogRead(leftEdge)  < edgeLimit);
  // Caso ele receba right como verdadeiro(1), vai fazer analogRead do sensor direito, retornando verdadeiro(1) caso esteja vendo a borda
}

//=====Início da função anyEdge
bool anyEdge(int *boardSide) 
{
  bool right = readEdge(0);          // Lê o sensor de borda direito
  bool left = readEdge(1);           // Lê o sensor de borda esquerdo
  *boardSide = left - right;         // boardSide resulta em 0 caso os dois sensores estiverem vendo, ou não estiverem vendo algo.
                                     // Caso um esteja e o outro não, boardSide será igual à 1
  return (left || right);            // Retorna left ou right, tem o objetivo de retornar um valor verdadeiro(1), não importando qual seja
                                     // Dessa forma, caso boardSide seja 0 e o valor retornado seja verdadeiro, está vendo algo, mesma coisa ao contrário
}

//=====Início da função readIR
bool readIR(bool right) 
{
  return right ? (digitalReadFast(rightIR)) : (digitalReadFast(leftIR));  
  // Caso ele receba right como verdadeiro(1), vai fazer analogRead do sensor direito, retornando verdadeiro(1) caso esteja vendo inimigo
}

//=====Início da função anyIR
bool anyIR(int *side)
{
  bool right = readIR(0);             // Lê o sensor IR direito
  bool left = readIR(1);              // Lê o sensor IR esquerdo
  *side = right - left;               // side resulta em 0 caso os dois sensores estiverem vendo, ou não estiverem vendo algo
                                      // Caso um esteja e outro não, side será igual a 1
  return (left || right);             // Retorna left ou right, tem o objetivo de retornar um valor verdadeiro(1), não importando qual seja
                                      // Dessa forma, caso side seja 0 e o valor returnado seja verdadeiro, está vendo algo, mesma coisa ao contrário
}

//=====Início da função edgeInterrupt
void edgeInterrupt()
{
  move(0, backPWM, 1);
  delayInterrupt = false;
}

// Usar interrupção para fazer estrategias de início

//=====Início da função IRInterrupt
void IRInterrupt()
{
  delayInterrupt = false;
}

void myDelay(unsigned long delayTime)
{
  unsigned long start = millis();
  while((millis() - start < delayTime) and delayInterrupt);
  delayInterrupt = true;
}
