//=====Inclusão das bibliotecas
#include <Arduino.h>
#include "startStop.h"
#include "constants.h"
#include "motors.h"

Button button1(button);
SoftwareSerial bluetooth(9, 10);

//=====Início da função waitButton
void waitButton() {
  while (1) {
    if (button1.pressed()) {
      break;
    }
  }
  }

//=====Início da função verifyToStopButton
void verifyToStopButton() {
  if (button1.pressed()) {
    while(1){
      stop();
      }
  }
}
  
