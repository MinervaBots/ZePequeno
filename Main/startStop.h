#ifndef STARTSTOP_H
#define STARTSTOP_H

#include <Button.h>

//void waitIR();
//void verifyToStopIR();
void waitButton();
bool verifyToStopButton();
void verifyOnButton();
void verifyButton();

extern Button button1;

#endif
