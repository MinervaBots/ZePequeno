#include <Arduino.h>

//Times
#define INITIAL_DELAY         1200 //Milliseconds. This value will be multiplied by four in initialDelay();
#define SELECTION_TIME        3000 //Milliseconds. When in strategy selection routine, that is the time to wait before confirm the strategy selected.

//Speed
#define PWM_MAX               511 //From 0 to 511
#define PWM_SEEK              255 //Mid Value
#define SPEED_OFFSET          511 //From 0 to 511

//Uncomment for Debug mode
//#define DEBUG

//Uncomment for Seek mode
//#define SEEK

//Opponents sensors
//#define NUM_SENSORS         2

#define LEFT_SENSOR           8
#define RIGHT_SENSOR          16

// Edge sensors
// #define NUM_EDGE_SENSOR    2

// #define LEFT_EDGE_SENSOR   6
// #define RIGHT_EDGE_SENSOR  17

//Buttons
#define STRATEGY_BUTTON       5
#define ON_BUTTON             7

//Ir Sensor
//#define IR_RECEIVER         22

//Led's
#define NUM_LEDS              5

#define STRATEGY_ONE          0
#define STRATEGY_TWO          1
#define STRATEGY_THREE        2
#define STRATEGY_FOUR         3
#define RUN_LED               4

//Motors
//#define NUM_MOTORS          2

#define LEFT_MOTOR_IN1        14
#define LEFT_MOTOR_IN2        15
#define LEFT_MOTOR_PWM        20

#define RIGHT_MOTOR_IN1       18
#define RIGHT_MOTOR_IN2       19
#define RIGHT_MOTOR_PWM       21

////////////////////////Global Variables//////////////////////////

unsigned int speedOffset = SPEED_OFFSET; //Value of speed compensation on the right or left turn
byte position = 0;
byte buttonValue = 0;
byte ledArray [NUM_LEDS] = {STRATEGY_ONE, STRATEGY_TWO, STRATEGY_THREE, STRATEGY_FOUR, RUN_LED};
byte leftIR;
byte rightIR;
byte strategy;

volatile byte buttonChange; //To be functional at interruption

unsigned long selectionTime = 0;

//////////////////////////////////////////////////////////////////

void
initRobot() {
  //Outputs
  pinMode(LEFT_MOTOR_IN1,OUTPUT);
  pinMode(LEFT_MOTOR_IN2, OUTPUT);
  pinMode(LEFT_MOTOR_PWM, OUTPUT);

  pinMode(RIGHT_MOTOR_IN1, OUTPUT);
  pinMode(RIGHT_MOTOR_IN2, OUTPUT);
  pinMode(RIGHT_MOTOR_PWM, OUTPUT);

  pinMode(STRATEGY_ONE, OUTPUT);
  pinMode(STRATEGY_TWO, OUTPUT);
  pinMode(STRATEGY_THREE, OUTPUT);
  pinMode(STRATEGY_FOUR, OUTPUT);
  pinMode(RUN_LED, OUTPUT);

  //Inputs
  pinMode(LEFT_SENSOR, INPUT);
  pinMode(RIGHT_SENSOR, INPUT);

  //pinMode(RIGHT_EDGE_SENSOR, INPUT);
  //pinMode(LEFT_EDGE_SENSOR, INPUT);

  pinMode(STRATEGY_BUTTON, INPUT_PULLUP);
  pinMode(ON_BUTTON, INPUT_PULLUP);

  //pinMode(IR_RECEIVER, INPUT);

  //analogWrite definitions
  analogWriteFrequency(LEFT_MOTOR_PWM, 93750); //Set 93750Hz frequency to LEFT_MOTOR_PIN and for all the others pins wich use the same Timer Registers. Include RIGHT_MOTOR_PWM pin.
  analogWriteResolution(9); //Values from 0 to 511

  //Debug
  #ifdef DEBUG
      Serial.begin(9600); //At Teensy 3.1, the baud rate will be always 12Mbit/s so the 9600 value here got no effect.
  #endif
}

//Interruption function
void
onButton() {
    buttonChange *= -1;
    detachInterrupt(ON_BUTTON);
}

//Define the strategy for the round
byte
strategyButton() {
  selectionTime = millis();
  digitalWriteFast(ledArray[buttonValue], HIGH);
  while ((millis() - selectionTime) <= SELECTION_TIME) {
    if (digitalReadFast(STRATEGY_BUTTON) == LOW){ //Connect the other terminal of microswitch at ground pin
      buttonValue += 1;
      if (buttonValue <= 3) { //Number of strategies
        delay(10);
        while (digitalReadFast(STRATEGY_BUTTON)==LOW){;};//Do nothing when pressing the microswitch
        delay(10);
        digitalWriteFast(ledArray[buttonValue], HIGH);
        selectionTime = millis();
      }
      else {
        buttonValue = 0;
        delay(10);
        while (digitalReadFast(STRATEGY_BUTTON)==LOW){;};
        delay(10);
        digitalWriteFast(ledArray[buttonValue], HIGH);
        selectionTime = millis();
      }
    }
  }
  return buttonValue;
}
//Initial delay; Blink the "run led", keep the selected "strategy led" on.
void
initialDelay(unsigned int time) {

  digitalWriteFast(ledArray[strategy], HIGH);
  digitalWriteFast(ledArray[4], LOW);
  delay(time);
  digitalWriteFast(ledArray[4], HIGH);
  delay(time);
  digitalWriteFast(ledArray[4], HIGH);
  delay(time);
  digitalWriteFast(ledArray[4], LOW);
  delay(time);
}

//Motor Control
void
forwardMotorControl(unsigned int pwm) {
  digitalWriteFast(RIGHT_MOTOR_IN1, HIGH);
  digitalWriteFast(RIGHT_MOTOR_IN2, LOW);
  analogWrite(RIGHT_MOTOR_PWM, pwm);

  digitalWriteFast(LEFT_MOTOR_IN1, LOW);
  digitalWriteFast(LEFT_MOTOR_IN2, HIGH);
  analogWrite(LEFT_MOTOR_PWM, pwm);
}

void
rightMotorControl(unsigned int pwm) {
  digitalWriteFast(RIGHT_MOTOR_IN1, LOW);
  digitalWriteFast(RIGHT_MOTOR_IN2, HIGH);
  analogWrite(RIGHT_MOTOR_PWM, pwm - speedOffset);

  digitalWriteFast(LEFT_MOTOR_IN1, LOW);
  digitalWriteFast(LEFT_MOTOR_IN2, HIGH);
  analogWrite(LEFT_MOTOR_PWM, pwm);
}

void
leftMotorControl(unsigned int pwm) {
  digitalWriteFast(RIGHT_MOTOR_IN1, LOW);
  digitalWriteFast(RIGHT_MOTOR_IN2, HIGH);
  analogWrite(RIGHT_MOTOR_PWM, pwm);

  digitalWriteFast(LEFT_MOTOR_IN1, LOW);
  digitalWriteFast(LEFT_MOTOR_IN2, HIGH);
  analogWrite(LEFT_MOTOR_PWM, pwm - speedOffset);
}

void
spinMotorControl(unsigned int pwm, byte strategy) {
  if(strategy == 0) { //Case 1:  Begin look to right; turn on its own axis
    digitalWriteFast(RIGHT_MOTOR_IN1, LOW);
    digitalWriteFast(RIGHT_MOTOR_IN2, HIGH);
    analogWrite(RIGHT_MOTOR_PWM, pwm);

    digitalWriteFast(LEFT_MOTOR_IN1, HIGH);
    digitalWriteFast(LEFT_MOTOR_IN2, LOW);
    analogWrite(LEFT_MOTOR_PWM, pwm);
  }
  if(strategy == 1) { //Case 2:  Begin look to left; turn on its own axis
    digitalWriteFast(RIGHT_MOTOR_IN1, HIGH);
    digitalWriteFast(RIGHT_MOTOR_IN2, LOW);
    analogWrite(RIGHT_MOTOR_PWM, pwm);

    digitalWriteFast(LEFT_MOTOR_IN1, LOW);
    digitalWriteFast(LEFT_MOTOR_IN2, HIGH);
    analogWrite(LEFT_MOTOR_PWM, pwm);
  }
}

void
enemyPosition(byte strategy) {
  //Position can assume four different values
  //0 ~ Not found a enemy
  //1 ~ Enemy founded by the right sensor
  //-1 ~ Enemy founded by the both sensors
  //-2 ~ Enemy founded by the left sensor
  digitalWriteFast(ledArray[strategy], HIGH);
  digitalWriteFast(ledArray[4], HIGH);
  leftIR = digitalReadFast(LEFT_SENSOR);
  rightIR = digitalReadFast(RIGHT_SENSOR);
  position = ((leftIR * -2) + (rightIR));
  if (position == 0)
      spinMotorControl(PWM_MAX,strategy);
  else {
    if (position == -1)
      forwardMotorControl(PWM_MAX);
    if (position == -2)
      leftMotorControl(PWM_MAX);
    if (position == 1)
      rightMotorControl(PWM_MAX);
  }
}

void
robotSeek() {
  digitalWriteFast(ledArray[0], HIGH);
  digitalWriteFast(ledArray[1], HIGH);
  digitalWriteFast(ledArray[2], HIGH);
  digitalWriteFast(ledArray[3], HIGH);
  digitalWriteFast(ledArray[4], HIGH);

  leftIR = digitalReadFast(LEFT_SENSOR);
  rightIR = digitalReadFast(RIGHT_SENSOR);
  position = ((leftIR * (-2)) + (rightIR));

  if (position == 0 || position == -1) { //Keep the two motors off
    digitalWriteFast(RIGHT_MOTOR_IN1, HIGH);
    digitalWriteFast(RIGHT_MOTOR_IN2, LOW);
    analogWrite(RIGHT_MOTOR_PWM, 0);

    digitalWriteFast(LEFT_MOTOR_IN1, HIGH);
    digitalWriteFast(LEFT_MOTOR_IN2, LOW);
    analogWrite(LEFT_MOTOR_PWM, 0);
  }
  else {
    if (position == -2) { //Counterclockwise spin
      digitalWriteFast(RIGHT_MOTOR_IN1, LOW);
      digitalWriteFast(RIGHT_MOTOR_IN2, HIGH);
      analogWrite(RIGHT_MOTOR_PWM, PWM_SEEK);

      digitalWriteFast(LEFT_MOTOR_IN1, HIGH);
      digitalWriteFast(LEFT_MOTOR_IN2, LOW);
      analogWrite(LEFT_MOTOR_PWM, PWM_SEEK);
    }
    if (position == 1) { //Clockwise spin
      digitalWriteFast(RIGHT_MOTOR_IN1, LOW);
      digitalWriteFast(RIGHT_MOTOR_IN2, HIGH);
      analogWrite(RIGHT_MOTOR_PWM, PWM_SEEK);

      digitalWriteFast(LEFT_MOTOR_IN1, HIGH);
      digitalWriteFast(LEFT_MOTOR_IN2, LOW);
      analogWrite(LEFT_MOTOR_PWM, PWM_SEEK);

    }
  }
}

