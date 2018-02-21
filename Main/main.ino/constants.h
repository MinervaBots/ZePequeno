SoftwareSerial bluetooth(9, 10); // verify pins (TX,RX)

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

#define accelerationRate 0.8 // test
#define edgeLimit 600 // test
#define maxPWM 100 // test
#define delayBackStart 50 // test
#define delayArchStart 50 // test
#define delayBackEdge 300 // test
#define delaySpinEdge 200 // test
#define attackF1delay 50 // test
#define attackF2delay 50 // test
#define attackS1delay 50 // test
#define attackS2delay 50 // test

#define SWITCH_ONE             4
#define SWITCH_TWO             3 // nÃ£o funcionando
#define SWITCH_THREE           2
#define SWITCH_FOUR            1

int forwardSpeed = 0;
Button button1(button);

void initialSet();

#endif

