#define ON_BUTTON              5

bool btn_state = false;

void setup() {
  pinMode(ON_BUTTON, INPUT_PULLUP);
  Serial.begin(9600); 
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
    Serial.println("ligado");
  }
  else {
    Serial.println("desligado");
  }
  delay(50);

}
