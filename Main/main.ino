//=====Inclusão das bibliotecas
#include "constants.h"
#include "startStop.h"
#include "strategies.h"
#include "motors.h"
#include "Button.h"
#include "sensors.h"

//=====Início do Setup
void setup() {
  //Starta Serial
  Serial.begin(9600);
  //while(!Serial);

  //Chamada das funções iniciais
  initialSet();                 // constants.h
  verifyStartStrategy();        // strategies.h
  verifySearchStrategy();       // strategies.h
  waitButton();                 // startStop.h
  digitalWrite(led, LOW);
  delay(5000);
  digitalWrite(led, HIGH);
  startStrategy();              // strategies.h
}

//=====Início da função loop
void loop() {
  verifyToStopButton();         // startStop.h 
  searchStrategy();             // strategies.h
}


//=====Início da função initialSet
void initialSet() {

  // Declaração de todos os pins
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(led, OUTPUT);
  pinMode(leftWheelPWM, OUTPUT);
  pinMode(rightWheelPWM, OUTPUT);
  pinMode(leftWheelP1, OUTPUT);
  pinMode(rightWheelP1, OUTPUT);
  pinMode(leftWheelP2, OUTPUT);
  pinMode(rightWheelP2, OUTPUT);
  pinMode(leftIR, INPUT);
  pinMode(rightIR, INPUT);
  pinMode(leftEdge, INPUT);
  pinMode(rightEdge, INPUT);
  pinMode(SWITCH_ONE, INPUT);
  pinMode(SWITCH_TWO, INPUT);
  pinMode(SWITCH_THREE, INPUT);
  pinMode(SWITCH_FOUR, INPUT);

  digitalWrite(led, HIGH);

  //Interrupção Borda
  attachInterrupt(leftEdge, edgeInterrupt, CHANGE); // ver se precisa mudar o CHANGE
  attachInterrupt(rightEdge, edgeInterrupt, CHANGE);

  //Interrupção IR
  attachInterrupt(leftIR, IRInterrupt, HIGH);  // checar se é HIGH
  attachInterrupt(rightIR, IRInterrupt, HIGH);
}
