#include "button.h"
#include "strategies.h"

void setup() {
  initialSet(); // constants.h
  waitButton(); // receptor.h
  delay(5000);
}

void loop() {
  radar(); // strategies.h
  verifyToStop(); // button.h
}
