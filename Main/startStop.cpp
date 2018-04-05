//=====Inclusão das bibliotecas
#include <Arduino.h>
#include "startStop.h"
#include "constants.h"
#include "motors.h"

Button button1(button, PULLUP);

//=====Início da função waitButton
void waitButton() {
  while (1) {
    if (button1.isPressed()) {
      break;
    }
  }
  }

//=====Início da função verifyToStopButton
void verifyToStopButton() {
  if (button1.isPressed()) {
    while(1){
      stop();
      }
  }
}
