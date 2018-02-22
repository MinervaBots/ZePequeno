#ifndef MOTORS_H
#define MOTORS_H

void move(float,float);
void stop();
void forward();
void backwards();
void spin(bool);
int speedToPWM(float);

extern int forwardSpeed;

#endif

