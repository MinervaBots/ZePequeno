#include "const.h"
#include "motors.h"
#include "sensors.h"
#include "startStop.h"
#include "strategies.h"
#include <IRremote.h>

bool IRBool = false;   // variável para ligar/desligar o robô

void setup()
{
  Serial.begin(9600);
  initialSet();
}

void loop() 
{
  waitIR(IRBool);
  digitalWrite(led, LOW);
  delay(5000);
  digitalWrite(led, HIGH);
  if(IRBool == true)                      // Caso o IR tenha sido acionado
  {
    while(1)                              // Entra no while
    {
      verifyToStopIR(IRBool);
      radarSearch();
      if(IRBool == false)  break;         //Caso o IR tenha sido acionado de novo,saí do while
    }
  }
}

//=== Início da função que seta tudo
void initialSet() {
  //button1.begin();
  IRrecv irrecv(RECV_PIN);

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
  //pinMode(leftEdge, INPUT);            funções comentadas pois n serão usadas por enquanto
  //pinMode(rightEdge, INPUT);
  //pinMode(SWITCH_ONE, INPUT);
  //pinMode(SWITCH_TWO, INPUT);
  //pinMode(SWITCH_THREE, INPUT);
  //pinMode(SWITCH_FOUR, INPUT);
  irrecv.enableIRIn();  //começa a receber
  
  digitalWrite(led, HIGH);
}
