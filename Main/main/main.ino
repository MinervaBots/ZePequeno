// implementar rampa de aceleraÃ§Ã£o

#include "constants.h"
#include "startStop.h"
#include "strategies.h"

void setup() {
  Serial.begin(9600);
  initialSet(); // constants.h
  verifySearchStrategy(); // strategies.h
  waitButton(); // startStop.h
  //waitBluetooth(); // startStop.h
  //delay(5000);
  //startStrategy(); // strategies.h
}

void loop() {
  //Serial.println("loop");
  verifyStartStrategy(); // strategies.h
  searchStrategy(); // strategies.h
  verifyToStopButton(); // startStop.h
  //verifyToStopBluetooth(); // startStop.h
}
