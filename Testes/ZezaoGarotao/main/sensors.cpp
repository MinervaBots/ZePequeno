#include <Arduino.h>
#include "sensors.h"
#include "const.h"

bool readIR(bool right)
{
  return right ? (digitalReadFast(rightIR)) : (digitalReadFast(leftIR));
}

bool anyIR(int* side)
{
  bool right = readIR(0);
  bool left = readIR(1);
  *side = right - left;
  return (left || right);
}
