#ifndef STARTSTOP_H              // Caso STARTSTOP_H não esteja declarado
#define STARTSTOP_H              // Define STARSTOP_H

#include <SoftwareSerial.h>
#include <Button.h>

//=====Declaração das funções
void waitBluetooth();
void verifyToStopBluetooth();
void waitButton();
void verifyToStopButton();

//=====Declaração dos objetos
extern Button button1;
extern SoftwareSerial bluetooth; // verify pins (TX,RX)

#endif
