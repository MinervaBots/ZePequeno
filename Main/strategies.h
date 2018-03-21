#ifndef STRATEGIES_H        // Se STRATEGIES_H não esteja declarado
#define STRATEGIES_H        // Define STRATEGIES_H

//=====Declaração das funções
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

extern int lastToSee;
extern void (*searchStrategy)();
extern void (*startStrategy)();

#endif
