#ifndef SENSORS_H           // Caso o SENSOR_H não esteja definido
#define SENSORS_H           // Define SENSORS_H


//======Declaração das funções
bool readIR(bool);
bool anyIR(int* side);
bool readEdge(bool);
bool anyEdge(int*);
bool strategyButton(int);
void IRInterrupt();
void myDelay(unsigned long);
void edgeInterrupt();
                             
#endif             
