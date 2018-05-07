#ifndef STARTSTOP_H              // Caso STARTSTOP_H não esteja declarado
#define STARTSTOP_H              // Define STARSTOP_H

#include <SoftwareSerial.h>
#include <Button.h>
#include <IRremote.h>

//=====Declaração das funções
void waitButtonOrIR();
void verifyToStopButtonOrIR();

//=====Declaração dos objetos
extern Button button1;
extern SoftwareSerial bluetooth; // verify pins (TX,RX)
extern IRRecv irrecv;

#endif
