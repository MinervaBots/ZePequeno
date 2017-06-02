#include <QTRSensors.h>
#define LEFT_IRSENSOR         10
#define RIGHT_IRSENSOR         9

#define LEFT_EDGESENSOR       18
#define RIGHT_EDGESENSOR      19

#define ON_BUTTON              5

#define LEFT_MOTOR_IN1        17
#define LEFT_MOTOR_IN2        16
#define LEFT_MOTOR_PWM        22
#define RIGHT_MOTOR_IN1       20
#define RIGHT_MOTOR_IN2       21
#define RIGHT_MOTOR_PWM       23

#define PWM_SEEK             350
#define PWM_SEEK_MINOR       160
#define PWM_MAX              511

#define LED                    0

#define SWITCH_ONE             4
#define SWITCH_TWO             3
#define SWITCH_THREE           2
#define SWITCH_FOUR            1

unsigned short leftIR;
unsigned short rightIR;
int number = 210;
bool btn_state = false;

void setup() {
  pinMode(LEFT_MOTOR_IN1, OUTPUT);
  pinMode(LEFT_MOTOR_IN2, OUTPUT);
  pinMode(LEFT_MOTOR_PWM, OUTPUT);
  pinMode(RIGHT_MOTOR_IN1, OUTPUT);
  pinMode(RIGHT_MOTOR_IN2, OUTPUT);
  pinMode(RIGHT_MOTOR_PWM, OUTPUT);

  pinMode(SWITCH_ONE, INPUT);
  pinMode(SWITCH_TWO, INPUT);
  pinMode(SWITCH_THREE, INPUT);
  pinMode(SWITCH_FOUR, INPUT);

  pinMode(LEFT_IRSENSOR, INPUT);
  pinMode(RIGHT_IRSENSOR, INPUT);

  pinMode(LEFT_EDGESENSOR, INPUT);
  pinMode(LEFT_EDGESENSOR, INPUT);

  pinMode(ON_BUTTON, INPUT_PULLUP);

  Serial.begin(9600);

  pinMode(LED, OUTPUT);
  digitalWrite(LED, HIGH);

  // QTRSensorsAnalog qtra((unsigned char[]) {LEFT_EDGESENSOR, RIGHT_EDGESENSOR}, 2);
}

void rightWheelForward()
{
  digitalWriteFast(RIGHT_MOTOR_IN1, HIGH);
  digitalWriteFast(RIGHT_MOTOR_IN2, LOW);
}



void leftWheelForward()
{
  digitalWriteFast(LEFT_MOTOR_IN1, HIGH);
  digitalWriteFast(LEFT_MOTOR_IN2, LOW);
}


void rightWheelBackward()
{
  digitalWriteFast(RIGHT_MOTOR_IN1, LOW);
  digitalWriteFast(RIGHT_MOTOR_IN2, HIGH);
}



void leftWheelBackward()
{
  digitalWriteFast(LEFT_MOTOR_IN1, LOW);
  digitalWriteFast(LEFT_MOTOR_IN2, HIGH);
}


void readIRSensors()
{
  leftIR = digitalReadFast(LEFT_IRSENSOR);
  rightIR = digitalReadFast(RIGHT_IRSENSOR);
}

void seekAndDestroy(boolean prefSide)
{
  readIRSensors();

  if (leftIR == 0 && rightIR == 1)
  {
    Serial.println("1");
    rightWheelForward();
    leftWheelForward();
    analogWrite(LEFT_MOTOR_PWM, PWM_SEEK);
    analogWrite(RIGHT_MOTOR_PWM, PWM_SEEK_MINOR);
    //readIRSensors();
  }

  else if (leftIR == 1 && rightIR == 0)
  {
    Serial.println("2");
    rightWheelForward();
    leftWheelForward();
    analogWrite(LEFT_MOTOR_PWM, PWM_SEEK_MINOR);
    analogWrite(RIGHT_MOTOR_PWM, PWM_SEEK);
    //readIRSensors();
  }

  else if (leftIR == 1 && rightIR == 1)
  {
    Serial.println("3");
    rightWheelForward();
    leftWheelForward();
    analogWrite(LEFT_MOTOR_PWM, PWM_MAX);
    analogWrite(RIGHT_MOTOR_PWM, PWM_MAX);
    //readIRSensors();
  }
  else if (leftIR == 0 && rightIR == 0 && prefSide == 0)
  {
    Serial.println("4");
    rightWheelBackward();
    leftWheelForward();
    analogWrite(LEFT_MOTOR_PWM, PWM_SEEK);
    analogWrite(RIGHT_MOTOR_PWM, PWM_SEEK);
  }
  else if (leftIR == 0 && rightIR == 0 && prefSide == 1)
  {
    Serial.println("5");
    rightWheelForward();
    leftWheelBackward();
    analogWrite(LEFT_MOTOR_PWM, PWM_SEEK);
    analogWrite(RIGHT_MOTOR_PWM, PWM_SEEK);
  }
}

void switchPrint() {
  number = (digitalReadFast(SWITCH_FOUR) + digitalReadFast(SWITCH_THREE) * 2 +  digitalReadFast(SWITCH_TWO) * 4 + digitalReadFast(SWITCH_ONE) * 8);
  Serial.print("Switch: ");
  Serial.println(number);
}

void verifyOnButton() {
  if (digitalReadFast(ON_BUTTON) == LOW) {
    delay(50);
    btn_state = !btn_state;
  }
}
void loop() {
  verifyOnButton();
  if (btn_state) {
    seekAndDestroy(false);
  }
  else {
    Serial.println("desligado");
  }
  delay(50);
}
