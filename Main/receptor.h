#include <Arduino.h>
#include "constants.h"
#include "motors.h"

#ifndef RECEPTOR_H
#define RECEPTOR_H

void waitReceptor() {
  while (not digitalRead(receptor)) {
  }
}

void verifyToStop() {
  while (digitalRead(receptor)) {
    stop();
  }
}


#endif
