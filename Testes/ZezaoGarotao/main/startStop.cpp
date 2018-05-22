#include <Arduino.h>
#include "startStop.h"
#include "const.h"
#include "motors.h"
#include <IRremote.h>

IRrecv irrecv(RECV_PIN);
decode_results results;
//Button button1(button);

void waitIR(bool IRBool)
{
  while(1)
  {
    if (irrecv.decode(&results))
    {
       irrecv.resume();
       IRBool = true;
       break;
    }
  }
}

void verifyToStopIR(bool IRBool)
{
   if (irrecv.decode(&results))
    {
      irrecv.resume();
      IRBool = false;
    }
}
