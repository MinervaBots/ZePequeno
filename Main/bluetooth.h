#include <Arduino.h>
#include "constants.h"
#include "motors.h"

#ifndef BLUETOOTH_H
#define BLUETOOTH_H

void waitButton() {
  bool ready = false;
  while (not ready) {
    if (bluetooth.available() > 0) {
      ready = (bluetooth.read() == 1);
  }
}

void verifyToStop() {
  if (bluetooth.available() > 0) {
    if bluetooth.read() == 0 {
      while(true) {}
    }
  }
}


#endif
