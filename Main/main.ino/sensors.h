#ifndef SENSORS_H
#define SENSORS_H

int lastToSee = -1;

bool readIR(bool);
int readIRs();
bool anyIR();
bool readEdge(bool);
bool anyEdge();
bool strategyButton(int);


#endif
