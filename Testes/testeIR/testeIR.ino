#define LEFT_IRSENSOR         10
#define RIGHT_IRSENSOR         9

void setup() {
  // put your setup code here, to run once:
  pinMode(LEFT_IRSENSOR, INPUT);
  pinMode(RIGHT_IRSENSOR, INPUT);

  Serial.begin(9600);
}

unsigned short leftIR;
unsigned short rightIR;

void readIRSensors(){
  leftIR = digitalReadFast(LEFT_IRSENSOR);
  rightIR = digitalReadFast(RIGHT_IRSENSOR);
}


void seekAndDestroy(boolean prefSide){
  readIRSensors();

  if (leftIR == 0 && rightIR == 1)
  {
    Serial.println("1");
  }

  else if (leftIR == 1 && rightIR == 0)
  {
    Serial.println("2");
  }
  else if (leftIR == 1 && rightIR == 1)
  {
    Serial.println("3");
  }
  else if (leftIR == 0 && rightIR == 0 && prefSide == 0)
  {
    Serial.println("4");
  }
  else if (leftIR == 0 && rightIR == 0 && prefSide == 1)
  {
    Serial.println("5");
  }
}

void loop() {
  seekAndDestroy(false);
}
