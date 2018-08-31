#include "constants.h"
#include "motors.h"
#include "sensors.h"
#include "startStop.h"
#include "strategies.h"
//#include <IRremote.h>
#include <EEPROM.h>

// variável para ligar/desligar o robô
void initialSet();

void setup()
{
  //Serial.begin(9600);
  initialSet();
  delay(1000);
}

void loop()
{
  waitButton();
  digitalWrite(led, HIGH);
  //Serial.println("Acendeu");
  verifyStartStrategy();
  verifySearchStrategy();
  delay(4900);
  digitalWrite(led, LOW);
  //Serial.println("Apagou");
  startStrategy();
  while (1)
  {
    //stop();
    searchStrategy();
    //radarSearch();
    //starSearch();
    if (verifyToStopButton())   break;
    //Serial.println("chegou no fim do loop");
  }
  delay(1000);
  //Serial.println("desligou");
}

//=== Início da função que seta tudo
void initialSet() {
  //button1.begin();
  //IRrecv irrecv(RECV_PIN);
  //decode_results results;

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
  //pinMode(button, INPUT);
  pinMode(leftEdge, INPUT);            //funções comentadas pois n serão usadas por enquanto
  pinMode(rightEdge, INPUT);
  pinMode(SWITCH_ONE, INPUT_PULLDOWN);
  pinMode(SWITCH_TWO, INPUT_PULLDOWN);
  pinMode(SWITCH_THREE, INPUT_PULLDOWN);
  pinMode(SWITCH_FOUR, INPUT_PULLDOWN);
  //irrecv.enableIRIn();  //começa a receber

}
