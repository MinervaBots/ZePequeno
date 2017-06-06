#define SWITCH_ONE             4
#define SWITCH_TWO             3
#define SWITCH_THREE           2
#define SWITCH_FOUR            1

void setup() {
  pinMode(SWITCH_ONE, INPUT);
  pinMode(SWITCH_TWO, INPUT);
  pinMode(SWITCH_THREE, INPUT);
  pinMode(SWITCH_FOUR, INPUT);

  Serial.begin(9600); 
}

int number = 210;

void switchPrint() {
  number = (digitalReadFast(SWITCH_FOUR) + digitalReadFast(SWITCH_THREE) * 2 +  digitalReadFast(SWITCH_TWO) * 4 + digitalReadFast(SWITCH_ONE) * 8);
  Serial.print("Switch: ");
  Serial.println(number);
}


void loop() {
  switchPrint();
}
