#include <Arduino.h>
#include "startStop.h"
#include "constants.h"
#include "motors.h"
//#include <IRremote.h>
#include <Button.h>

//IRrecv irrecv(RECV_PIN);
//decode_results results;
Button button1 = Button(button,PULLUP);
int aux = 0;
bool btn_state = false;
int count = 0;

/*void waitIR()
{
  while (1)
  {
    if (irrecv.decode(&results))
    {
      Serial.println(results.value, HEX);
      irrecv.resume();
      break;
    }
  }
}

void verifyToStopIR()
{
  if (irrecv.decode(&results))
  {
    count++;
    if (count >= 5)
    {
      while (1)
      {
        Serial.println(results.value, HEX);
        Serial.println("entrou while StopIR");
        irrecv.resume();
        stop();
      }
    }
  }
}
*/

void waitButton() {
  while (1) {
    if (button1.isPressed()) {
      //Serial.println("pressionado");
      break;
    }
  }
  }

bool verifyToStopButton() {
  if (button1.isPressed()) {
    //Serial.println("Pressionado parou");
    stop();
    return true;
    //while(1){
      //Serial.println("Pressionado parou");
      //stop();
      //}
  }
}
