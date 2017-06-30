#define ON_BUTTON              5

bool btn_state = false;
int aux = 0;

void setup() {
  pinMode(ON_BUTTON, INPUT_PULLUP);
  Serial.begin(9600);
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
    Serial.println("ligado");
  }
  else if (aux != 0) {
    aux = 0;
    btn_state = false;
    Serial.println("desligando");
    delay(150);
  }
  else{
    Serial.println("desligando");
  }
}
