#include <Arduino.h>
#include "sensors.h"
#include "const.h"

float lastIRreading = 0;
float readIR()
{
  float reading = digitalReadFast(rightIR) + digitalReadFast(leftIR);
  float ret = (1.0 - 0.8) * lastIRreading + reading * 0.8;
  lastIRreading = reading;
  return ret;
}

bool readIR(bool right)
{
  return right ? (digitalReadFast(rightIR)) : (digitalReadFast(leftIR));
}

bool anyIR(int* side)
{
  bool right = readIR(0);
  bool left = readIR(1);
  *side = right - left;
  return (left || right);
}

bool readEdge(bool right)
{
  /*
  Serial.print("Edge Direita: ");
  Serial.print(analogRead(rightEdge));
  Serial.print("   ||    Edge Esquerda: ");
  Serial.println(analogRead(leftEdge));
  */
  return (right ? (analogRead(rightEdge) < edgeLimit) : (analogRead(leftEdge) < edgeLimit));
}

bool anyEdge(int *boardSide)
{
  bool right = readEdge(0);
  bool left = readEdge(1);
  *boardSide = right - left;
  return (left || right);  
}

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
  if (selectionButton == 4)
  {
    return digitalRead(SWITCH_FOUR);  
  }                                   // Caso botão 4 seja selecionado, vai retornar SWITCH_FOUR
}
