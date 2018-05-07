//=====Inclusão das bibliotecas
#include <Arduino.h>
#include "startStop.h"
#include "constants.h"
#include "motors.h"
#include <IRremote.h>

Button button1(button);
SoftwareSerial bluetooth(9, 10);

//Declaração do IR
IRrecv irrecv(RECV_PIN);
irrecv.enableIRIn(); //Start the receiver

//=====Início da função waitButton
void waitButtonOrIR() {
  while (1) {
    if (button1.pressed() || irrecv.decode(&results()) ) {
      irrecv.resume();
      break;
    }
  }
  }

//=====Início da função verifyToStopButton
void verifyToStopButtonOrIR() {
  if (button1.pressed() || irrecv.decode(&results))) {
    while(1){
      stop();
      }
  }
}
  
