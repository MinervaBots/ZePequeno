#include <Arduino.h>
#include "constants.h"
#include "motors.h"

#ifndef BUTTON_H
#define BUTTON_H

void waitButton() {
  while (not digitalRead(button)) {
  }
}

void verifyToStop() {
  while (digitalRead(button)) {
    stop();
  }
}


#endif
