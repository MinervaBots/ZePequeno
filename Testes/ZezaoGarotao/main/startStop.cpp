#include <Arduino.h>
#include "startStop.h"
#include <constants.h>
#include "motors.h"
#include <IRremote.h>

IRrecv irrecv(RECV_PIN);
decode_results results;
Button button1(button);
SoftwareSerial bluetooth(9, 10);


void waitBluetooth() {
  bool ready = false;
  while (not ready) {
    if (bluetooth.available() > 0) {
      ready = (bluetooth.read() == 1);
    }
  }
}

void verifyToStopBluetooth() {
  if (bluetooth.available() > 0) {
    if (bluetooth.read() == 0) {
      while(true) {}
    }
  }
}

void waitButton() {
  while (1) {
    if (button1.pressed()) {
      break;
    }
  }
  }

void verifyToStopButton() {
  if (button1.pressed()) {
    while(1){
      stop();
      }
  }
}

void waitIR()
{
  while(1)
  {
    if (irrecv.decode(&results))
    {
       irrecv.resume();
       break;
    }
  }
}

void verifyToStopIR()
{
    if (irrecv.decode(&results))
    {
      while(1)
      {
        stop();
      }
    }
}

