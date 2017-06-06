#include <QTRSensors.h>
#define LEFT_EDGESENSOR       18
#define RIGHT_EDGESENSOR      19

void setup() {
  pinMode(LEFT_EDGESENSOR, INPUT);
  pinMode(LEFT_EDGESENSOR, INPUT);

  Serial.begin(9600);
}

  unsigned short leftEdge;
  unsigned short rightEdge;
  int constSensor = 600;
  
void readEdgeSensors() {
  leftEdge = analogRead(LEFT_EDGESENSOR);
  rightEdge = analogRead(RIGHT_EDGESENSOR);
}

void seeEdge() {
  readEdgeSensors();
  if (leftEdge < constSensor && rightEdge > constSensor)
  {
    Serial.println("10");
  }
  else if (leftEdge > constSensor && rightEdge < constSensor)
  {
    Serial.println("20");
  }
  else if (leftEdge > constSensor && rightEdge > constSensor)
  {
    Serial.println("30");
  }
  else if (leftEdge < constSensor && rightEdge < constSensor)
  {
    Serial.println("40");
  }
}
void loop() {
  seeEdge();
}
