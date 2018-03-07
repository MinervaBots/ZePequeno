#ifndef STARTSTOP_H
#define STARTSTOP_H

#include <SoftwareSerial.h>
#include <Button.h>

void waitBluetooth();
void verifyToStopBluetooth();
void waitButton();
void verifyToStopButton();

extern Button button1;
extern SoftwareSerial bluetooth; // verify pins (TX,RX)

#endif
