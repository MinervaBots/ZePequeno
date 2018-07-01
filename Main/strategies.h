#ifndef STRATEGIES_H
#define STRATEGIES_H

void radarSearch();         // xxx0
void starSearch();
void verifySearchStrategy();
void verifyStartStrategy();
void nothing();


void rightFlank();
void leftFlank();
void leftDibre();

extern int lastToSee;
extern void (*searchStrategy)();
extern void (*startStrategy)();

#endif
