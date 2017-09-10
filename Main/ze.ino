#include "bluetooth.h"
#include "strategies.h"

void setup() {
  initialSet(); // constants.h
  verifyStartStrategy(); // strategies.h
  verifySearchStrategy(); // strategies.h
  waitBluetooth(); // button.h
  delay(5000);
  startStrategy(); // strategies.h
}

void loop() {
  searchStrategy(); // strategies.h
  verifyToStop(); // button.h
}
