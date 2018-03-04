#ifndef CONSTANTS_H
#define CONSTANTS_H

//#define convertPWM 0.31 // test
#define maxPWM 255 
#define maxStarPWM 75//maxPWM * convertPWM 
#define backPWM 150


#define delayBackEdge 200//((int)((100.0 / maxPWM) * 300.0)) 
#define delaySpinEdge 110//((int)((100.0 / maxPWM) * 200.0)) 

#define accelerationRate 0.8 // test
#define edgeLimit 600 
#define delayBackStart 140

#define arcPWM 80
#define delayArchStartRight 120
#define delayBackLookingRight 190
#define archAngleRight 0.45

#define delayArchStartLeft 120
#define delayBackLookingLeft 190
#define archAngleLeft 0.45

#define attackF1delayRight 190 
#define attackF2delayRight 180 
#define attackS1delayRight 110 
#define attackS2delayRight 150 

#define attackF1delayLeft 190 
#define attackF2delayLeft 180 
#define attackS1delayLeft 110 
#define attackS2delayLeft 150

#define led 0
#define leftWheelPWM 21
#define rightWheelPWM 20
#define leftWheelP1 18
#define leftWheelP2 19
#define rightWheelP1 15
#define rightWheelP2 14
#define leftIR 10
#define rightIR 9
#define button 5
#define leftEdge 16
#define rightEdge 17

#define SWITCH_ONE             4
#define SWITCH_TWO             3
#define SWITCH_THREE           2
#define SWITCH_FOUR            1


#endif

