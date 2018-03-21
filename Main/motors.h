#ifndef MOTORS_H         // Caso MOTORS_H não esteja definido
#define MOTORS_H         // Define MOTORS_H

//float forwardSpeed = 0;

//=====Declaração das funções
void move(float);
void move(float angular, int maxPwm, bool reverse = false);
void stop();
void moveLooking(unsigned int delayToSpin, int movePWM, int lastToSee = 0, bool reverse = false);
void spin(bool);
void forward();

#endif
