// implementar rampa de aceleração

#include "startStop.h"
#include "strategies.h"

void setup() {
  initialSet(); // constants.h
  verifyStartStrategy(); // strategies.h
  verifySearchStrategy(); // strategies.h
  waitButton(); // startStop.h
  //waitBluetooth(); // startStop.h
  delay(5000);
  startStrategy(); // strategies.h
}

void loop() {
  searchStrategy(); // strategies.h
  verifyToStopButton(); // startStop.h
  //verifyToStopBluetooth(); // startStop.h
}
