
#define LEFT_IRSENSOR         10
#define RIGHT_IRSENSOR         9

#define LEFT_EDGESENSOR       16
#define RIGHT_EDGESENSOR      17

#define ON_BUTTON              5

#define LEFT_MOTOR_IN1        15
#define LEFT_MOTOR_IN2        14
#define LEFT_MOTOR_PWM        20
  
#define RIGHT_MOTOR_IN1       18
#define RIGHT_MOTOR_IN2       19                // As portas dos motores sao essas, motor que conecta na direita, olhando a placa de cima (em formato de T)
#define RIGHT_MOTOR_PWM       21

#define PWM_SEEK             350
#define PWM_SEEK_MINOR       160
#define PWM_MAX              511

#define constSensor          600

#define LED                    0

#define SWITCH_ONE             4
#define SWITCH_TWO             3       //Tudo certo
#define SWITCH_THREE           2
#define SWITCH_FOUR            1

unsigned short leftIR;
unsigned short rightIR;
unsigned short leftEdge;
unsigned short rightEdge;
int aux = 0;
int number = 210;
bool btn_state = false;
bool prefSide = false;

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


void rightWheelForward() {
  digitalWriteFast(RIGHT_MOTOR_IN1, HIGH);
  digitalWriteFast(RIGHT_MOTOR_IN2, LOW);
}


void leftWheelForward() {
  digitalWriteFast(LEFT_MOTOR_IN1, LOW);
  digitalWriteFast(LEFT_MOTOR_IN2, HIGH);
}


void rightWheelBackward() {
  digitalWriteFast(RIGHT_MOTOR_IN1, LOW);
  digitalWriteFast(RIGHT_MOTOR_IN2, HIGH);
}



void leftWheelBackward() {
  digitalWriteFast(LEFT_MOTOR_IN1, HIGH);
  digitalWriteFast(LEFT_MOTOR_IN2, LOW);
}


void readIRSensors() {
  leftIR = digitalReadFast(LEFT_IRSENSOR);
  rightIR = digitalReadFast(RIGHT_IRSENSOR);
}

void readEdgeSensors() {
  leftEdge = analogRead(LEFT_EDGESENSOR);
  rightEdge = analogRead(RIGHT_EDGESENSOR);
}

void seeEdge() {
  readEdgeSensors();
  if (leftEdge < constSensor && rightEdge > constSensor)
  {
    Serial.println("10");
    rightWheelForward();
    leftWheelBackward();
    analogWrite(LEFT_MOTOR_PWM, PWM_MAX);
    analogWrite(RIGHT_MOTOR_PWM, PWM_SEEK);
    delay(100);
  }
  else if (leftEdge > constSensor && rightEdge < constSensor)
  {
    Serial.println("20");
    rightWheelBackward();
    leftWheelForward();
    analogWrite(LEFT_MOTOR_PWM, PWM_SEEK);
    analogWrite(RIGHT_MOTOR_PWM, PWM_MAX);
    delay(100);
  }
  else if (leftEdge < constSensor && rightEdge < constSensor)
  {
    Serial.println("30");
    rightWheelBackward();
    leftWheelBackward();
    analogWrite(LEFT_MOTOR_PWM, PWM_MAX);
    analogWrite(RIGHT_MOTOR_PWM, PWM_MAX);
    delay(100);
  }
  else if (leftEdge > constSensor && rightEdge > constSensor)
  {
    Serial.println("40");
    rightWheelForward();
    leftWheelForward();
    analogWrite(LEFT_MOTOR_PWM, PWM_MAX);              // Apagar depois
    analogWrite(RIGHT_MOTOR_PWM, PWM_MAX);
    delay(100);
  }
}

void seekAndDestroy(boolean prefSide) {
  readIRSensors();

  if (leftIR == 0 && rightIR == 1)
  {
    Serial.println("1");
    rightWheelForward();
    leftWheelForward();
    analogWrite(LEFT_MOTOR_PWM, PWM_SEEK);
    analogWrite(RIGHT_MOTOR_PWM, PWM_SEEK_MINOR);
    prefSide = 0;
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
    prefSide = 1;
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
  bool newState = btn_state;
  if (digitalReadFast(ON_BUTTON) == LOW) {
    newState = !btn_state;
  }
  if (newState != btn_state) {
    btn_state = newState;
    delay(500);
  }
}


void loop() {
  verifyOnButton();
  if (btn_state) {
    if (aux == 0) {
      Serial.println("ligando");
      delay(5000);
      aux = 1;
    }
    
    Serial.println("ligado");                     //todo o codigo dele ligado deve ficar nesse bloco
    seekAndDestroy(prefSide);
    seeEdge();
  }
  else if (aux != 0) {
    aux = 0;
    btn_state = false;
    Serial.println("desligando");
    delay(150);
  }
  else{
    Serial.println("desligado");
    analogWrite(LEFT_MOTOR_PWM, 0);
    analogWrite(RIGHT_MOTOR_PWM, 0);
    delay(100);
  }
}
