#ifndef MOTORS_H
#define MOTORS_H

void move(float);
void move(float angular, int maxPwm, bool reverse = false);
void stop();
void spin(bool);

#endif

