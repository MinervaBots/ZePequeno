#ifndef SENSORS_H
#define SENSORS_H


bool readIR(bool);
//int readIRs();
bool anyIR(int* side);
bool readEdge(bool);
bool anyEdge(int*);
bool strategyButton(int);


#endif
