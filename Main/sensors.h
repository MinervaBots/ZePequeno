#ifndef SENSORS_H
#define SENSORS_H

float readIR();
bool readIR(bool);
bool anyIR(int *);
bool anyEdge(int *);
bool readEdge(bool);
bool strategyButton(int);

#endif
