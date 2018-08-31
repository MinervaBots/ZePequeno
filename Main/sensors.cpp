#include <Arduino.h>
#include "sensors.h"
#include "constants.h"
#include "QTRSensors.h"

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
  bool right = readIR(true);
  bool left = readIR(false);
  *side = right - left;      //direita =  1  || esquerda =  -1  || os dois = 0
  return (left || right);
}

bool readEdge(bool right)
{
  unsigned int reading;
  if (right) {
    rightSensor.readCalibrated(&reading);
  }
  else {
    leftSensor.readCalibrated(&reading);
  }
  return (reading < edgeLimit);
}

bool anyEdge(int *boardSide)
{
  bool right = readEdge(true);
  bool left = readEdge(false);
  *boardSide = right - left;  // 1 ou -1
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

QTRSensorsAnalog rightSensor((unsigned char[]){
  rightEdge
}, 1, 1);

QTRSensorsAnalog leftSensor((unsigned char[]){
  leftEdge
}, 1, 1);

void calibrateSensors()
{
  rightSensor.calibrate();
  leftSensor.calibrate();
}
