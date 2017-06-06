
#define LEFT_MOTOR_IN1        17
#define LEFT_MOTOR_IN2        16
#define LEFT_MOTOR_PWM        22

void setup() {
  // put your setup code here, to run once:
  pinMode(LEFT_MOTOR_IN1, OUTPUT);
  pinMode(LEFT_MOTOR_IN2, OUTPUT);
  pinMode(LEFT_MOTOR_PWM, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWriteFast(LEFT_MOTOR_IN1, HIGH);
  digitalWriteFast(LEFT_MOTOR_IN2, LOW);
  digitalWriteFast(LEFT_MOTOR_PWM,100);
}
