#ifndef MOTORS_H
#define MOTORS_H

//float forwardSpeed = 0;

void move(float);
void move(float angular, int maxPwm, bool reverse = false);
void stop();
void moveLooking(unsigned int delayToSpin, int movePWM, int lastToSee = 0, bool reverse = false);
void spin(bool);
void forward();
void forwardRadar();

#endif
