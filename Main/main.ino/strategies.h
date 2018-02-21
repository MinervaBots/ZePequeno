#ifndef STRATEGIES_H
#define STRATEGIES_H

void starSearch();          // xxx1
void radarSearch();         // xxx0

void nothing();             // 000x
void backwardStart();       // 001x
void archStartRight();      // 010x
void archStartLeft();       // 011x
void attackStartRight();    // 100x
void attackStartLeft();     // 101x
void spinStartLeft();       // 110x
void spinStartRight();      // 111x

void avoidEdge();

void verifyStartStrategy();
void verifySearchStrategy();

void (*searchStrategy)();
void (*startStrategy)();

#endif

