#ifndef CONSTANTS_H
#define CONSTANTS_H

//#define convertPWM 0.31 // test
#define maxPWM 100
#define maxStarPWM 100//maxPWM * convertPWM 
#define backPWM 100


#define delayBackEdge 200//((int)((100.0 / maxPWM) * 300.0)) 
#define delaySpinEdge 200//((int)((100.0 / maxPWM) * 200.0)) 

#define accelerationRate 0.0006 // test
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

#define led 11
#define leftWheelPWM 21
#define rightWheelPWM 20
#define leftWheelP1 18
#define leftWheelP2 19
#define rightWheelP1 16
#define rightWheelP2 17
#define leftIR 9
#define rightIR 0
#define button 12
#define leftEdge 14
#define rightEdge 23

#define SWITCH_ONE             6
#define SWITCH_TWO             5
#define SWITCH_THREE           2
#define SWITCH_FOUR            1


#endif

