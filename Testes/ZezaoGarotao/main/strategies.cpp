#include <Arduino.h>
#include "motors.h"
#include "sensors.h"
#include "strategies.h"
#include "const.h"

int lastToSee = -1;

void radarSearch()
{
  int side;
  if(anyIR(&side)) 
  {
    if (side == 0)
    {
      forward();
    }
    else 
    {
      move(side*0.8, maxPWM);
    }
    lastToSee = side;
  }
  else 
  {
    move(lastToSee, maxPWM*0.4);
  }
}
