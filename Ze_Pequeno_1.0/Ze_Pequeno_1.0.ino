
#define LEFT_IRSENSOR         11
#define RIGHT_IRSENSOR        12

#define LEFT_EDGESENSOR       18
#define RIGHT_EDGESENSOR      19

#define NUM_LEDS               7
//Na placa só tem 1 LEDs
#define TEENSY_LED             7

#define RUN_LED                0

//Strategy Switch
#define SWITCH_ONE             4
#define SWITCH_TWO             3
#define SWITCH_THREE           2
#define SWITCH_FOUR            1


#define ON_BUTTON              7
//#define STRATEGY_BUTTON      5

#define LEFT_MOTOR_IN1        17
#define LEFT_MOTOR_IN2        16
#define LEFT_MOTOR_PWM        24
//Não temos certeza que o motor A é o esquerdo e o B é o direito, se tiver errado, inverter valores
#define RIGHT_MOTOR_IN1       20
#define RIGHT_MOTOR_IN2       21
#define RIGHT_MOTOR_PWM       25

#define PWM_SEEK              511             // 400 para reducao 20:1      511 para reducao 50:1
#define PWM_SEEK_MINOR        160              // 90 para reducao 20:1      200 para reducao 50:1

//#define PWM_SPIN              200
#define PWM_MAX               511             // 500 para reducao 20:1      511 para reducao 50:1
#define REVERSE_TIME          200

#define DEBOUNCING_TIME       200

unsigned short strategia;
float error = 0;
unsigned short power;
unsigned short leftIR;
unsigned short rightIR;

unsigned short leftES;
unsigned short rightES;

boolean foundEnemyVar = false;
boolean foundEdgeVar = false;
boolean prefSide = false;

bool btn_state = true;
float derivative;
float integral = 0;
void initRobot() {
  //Outputs
  pinMode(LEFT_MOTOR_IN1, OUTPUT);
  pinMode(LEFT_MOTOR_IN2, OUTPUT);
  pinMode(LEFT_MOTOR_PWM, OUTPUT);
  pinMode(RIGHT_MOTOR_IN1, OUTPUT);
  pinMode(RIGHT_MOTOR_IN2, OUTPUT);
  pinMode(RIGHT_MOTOR_PWM, OUTPUT);


  pinMode(RUN_LED, OUTPUT);
  pinMode(TEENSY_LED, OUTPUT);

  //Inputs
  pinMode(LEFT_IRSENSOR, INPUT);
  pinMode(RIGHT_IRSENSOR, INPUT);
  pinMode(ON_BUTTON, INPUT_PULLUP);

  pinMode(SWITCH_ONE, INPUT);
  pinMode(SWITCH_TWO, INPUT);
  pinMode(SWITCH_THREE, INPUT);
  pinMode(SWITCH_FOUR, INPUT);

  digitalWriteFast(TEENSY_LED, HIGH);

  analogWriteResolution(9);
  analogWriteFrequency(LEFT_MOTOR_PWM, 50000);

  Serial.begin(9600);

#if defined (DEBUG_SERIAL)  || defined (DEBUG_IR_CONTROLLER)
  Serial.begin(9600); //At Teensy 3.1, the baud rate will be always 12Mbit/s so the 9600 value here got no effect.
#endif
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

void blindTurn()
{
  int turnTime = millis();
  delay(50);

  while (!foundEnemyVar || (turnTime - millis() < 800))        //era 600
  {
    rightWheelForward();
    leftWheelForward();
    analogWrite(RIGHT_MOTOR_PWM, PWM_SEEK);                           //400  checar valores PWM
    analogWrite(LEFT_MOTOR_PWM, PWM_SEEK_MINOR);                      //100
    readIRSensors();
  }

  /*
     while (!enemyFound || (turnTime - initialTimeTurn < 400))
    {
      leftWheelForward();
      rightWheelBackward();
      analogWrite(RIGHT_MOTOR_PWM, 100);
      analogWrite(LEFT_MOTOR_PWM, 100);
      readIRSensors();
    }

    while (!enemyFound || (turnTime - initialTimeTurn < 400))
    {
      leftWheelForward();
      rightWheelForward();
      analogWrite(RIGHT_MOTOR_PWM, 100);
      analogWrite(LEFT_MOTOR_PWM, 100);
      readIRSensors();
    }
  */
}

void starStrategy()
{
  readEdgeSensors();
  if (prefSide == 0)
  {
    rightWheelBackward();
    leftWheelForward();
    analogWrite(LEFT_MOTOR_PWM, PWM_SEEK);
    analogWrite(RIGHT_MOTOR_PWM, PWM_SEEK);
    delay(100);                                        //testar delay
    while (!foundEdgeVar)
    {
      readEdgeSensors();
      rightWheelForward();
      leftWheelForward();
      analogWrite(LEFT_MOTOR_PWM, PWM_MAX);
      analogWrite(RIGHT_MOTOR_PWM, PWM_MAX);
    }
  }
  else if (prefSide == 1)
  {
    rightWheelForward();
    leftWheelBackward();
    analogWrite(LEFT_MOTOR_PWM, PWM_SEEK);
    analogWrite(RIGHT_MOTOR_PWM, PWM_SEEK);
    delay(100);
    while (!foundEdgeVar)
    {
      readEdgeSensors();
      rightWheelForward();
      leftWheelForward();
      analogWrite(LEFT_MOTOR_PWM, PWM_MAX);
      analogWrite(RIGHT_MOTOR_PWM, PWM_MAX);
    }
  }
}

void readIRSensors()
{
  leftIR = digitalReadFast(LEFT_IRSENSOR);
  rightIR = digitalReadFast(RIGHT_IRSENSOR);

  if (leftIR == 1 || rightIR == 1)
  {
    foundEnemyVar = true;
  }
}

void seekAndDestroy(boolean prefSide)
{
  leftIR = digitalReadFast(LEFT_IRSENSOR);
  rightIR = digitalReadFast(RIGHT_IRSENSOR);

  //turnTime = millis();
  // delay(50);

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
    rightWheelForward();
    leftWheelForward();
    analogWrite(LEFT_MOTOR_PWM, PWM_MAX);
    analogWrite(RIGHT_MOTOR_PWM, PWM_MAX);
    //readIRSensors();
  }
  else if (leftIR == 0 && rightIR == 0 && prefSide == 0)
  {
    rightWheelBackward();
    leftWheelForward();
    analogWrite(LEFT_MOTOR_PWM, PWM_SEEK);
    analogWrite(RIGHT_MOTOR_PWM, PWM_SEEK);
  }
  else if (leftIR == 0 && rightIR == 0 && prefSide == 1)
  {
    rightWheelForward();
    leftWheelBackward();
    analogWrite(LEFT_MOTOR_PWM, PWM_SEEK);
    analogWrite(RIGHT_MOTOR_PWM, PWM_SEEK);
  }
}


void selectStrategy()
{
  strategia = (digitalReadFast(SWITCH_FOUR) + digitalReadFast(SWITCH_THREE) * 2 +  digitalReadFast(SWITCH_TWO) * 4 + digitalReadFast(SWITCH_ONE) * 8);

  if (strategia == 0) {                             //Giro no proprio eixo pra direita
    rightWheelBackward();
    leftWheelForward();
    analogWrite(LEFT_MOTOR_PWM, PWM_SEEK);
    analogWrite(RIGHT_MOTOR_PWM, PWM_SEEK);
  }
  else if (strategia == 1)                          //Giro no proprio eixo pra esquerda
  {
    rightWheelForward();
    leftWheelBackward();
    analogWrite(LEFT_MOTOR_PWM, PWM_SEEK);
    analogWrite(RIGHT_MOTOR_PWM, PWM_SEEK);
  }
  else if (strategia == 3)                           //Pequeno arco pra direita
  {
    rightWheelForward();
    leftWheelForward();
    analogWrite(LEFT_MOTOR_PWM, PWM_SEEK);
    analogWrite(RIGHT_MOTOR_PWM, PWM_SEEK_MINOR);

  }
  else if (strategia == 4)                             //Pequeno arco pra esquerda
  {
    rightWheelForward();
    leftWheelForward();
    analogWrite(LEFT_MOTOR_PWM, PWM_SEEK_MINOR);
    analogWrite(RIGHT_MOTOR_PWM, PWM_SEEK);
  }
  else if (strategia == 5)
  {
    seekAndDestroy(prefSide);
  }
  else if (strategia == 6)
  {
    blindTurn();
  }
  else if (strategia == 7)
  {
    starStrategy();
  }
}

void readEdgeSensors()
{
  leftES = digitalReadFast(LEFT_EDGESENSOR);
  rightES = digitalReadFast(RIGHT_EDGESENSOR);
  if (leftES == 1 && rightES == 0)
  {
    foundEdgeVar = 1;
    prefSide = 0;
  }
  else if (leftES == 0 && rightES == 1)
  {
    foundEdgeVar = 1;
    prefSide = 1;
  }
  else if (leftES == 1 && rightES == 1)
  {
    foundEdgeVar = 1;
  }
  else
  {
    foundEdgeVar = 0;
  }
}

void verifyOnButton()
{
  if (digitalReadFast(ON_BUTTON) == LOW)
  {
    delay(200);
    btn_state = !btn_state;
  }
}

void setup()
{
  initRobot();
}

void loop()
{
  while (btn_state)
  {
    verifyOnButton();
  }
  //Wait start button
  digitalWriteFast(RUN_LED, HIGH);                //Initial delay
  delay(5000);
  selectStrategy();
  while (digitalReadFast(ON_BUTTON))
  {
    readEdgeSensors();
    seekAndDestroy(prefSide);
  }
  analogWrite(LEFT_MOTOR_PWM, 0);
  analogWrite(RIGHT_MOTOR_PWM, 0);
  btn_state = true;
  delay(500);
  digitalWriteFast(RUN_LED, LOW);
}
