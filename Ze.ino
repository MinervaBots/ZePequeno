#include "Constants.h"

void
setup() {
  initRobot();
  //On-button interrupt
  attachInterrupt(ON_BUTTON, onButton, CHANGE);
  strategy =  strategyButton();
}

void
loop() {
  #ifdef SEEK
    while(true) {
      robotSeek();
    }
  #endif
  if (buttonChange == 1) {
    initialDelay(INITIAL_DELAY);
    enemyPosition(strategy);
  }
}