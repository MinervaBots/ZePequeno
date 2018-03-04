#ifndef MOTORS_H
#define MOTORS_H

void move(float);
void move(float angular, int maxPwm, bool reverse = false);
void stop();
void moveLooking(unsigned int delayToSpin, int movePWM, int lastToSee = 0, bool reverse = false);
void spin(bool);

#endif

