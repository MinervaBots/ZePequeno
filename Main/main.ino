//=====Inclusão das bibliotecas
#include "constants.h"
#include "startStop.h"
#include "strategies.h"
#include "motors.h"


//=====Início do Setup
void setup() {
  //Starta Serial
  Serial.begin(9600);
  //while(!Serial);

  //Interrupção Borda
  attachInterrupt(InterruptEdgePinA, EdgeInterrupt, CHANGE);
  attachInterrupt(InterruptEdgePinB, EdgeInterrupt, CHANGE);
  
  //Interrupção IR
  attachInterrupt(InterruptLeftIRPin, IRInterrupt, CHANGE); //ver precisa mudar o CHANGE
  attachInterrupt(InterruptRightIRPin, IRInterrupt, CHANGE);

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
  
  // Declaração do botão
  button1.begin();

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
}