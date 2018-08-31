#ifndef SENSORS_H
#define SENSORS_H

#include "QTRSensors.h"

float readIR();
bool readIR(bool);
bool anyIR(int *);
bool anyEdge(int *);
bool readEdge(bool);
bool strategyButton(int);
void calibrateSensors();

extern QTRSensorsAnalog rightSensor;

extern QTRSensorsAnalog leftSensor;



#endif
