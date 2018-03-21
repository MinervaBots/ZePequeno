//=====Inclusão das bibliotecas
#include <Arduino.h>
#include "motors.h"
#include "constants.h"
#include "sensors.h"

float forwardSpeed = 0;

 //=====Início da função move
void move(float angular, int maxPwm, bool reverse)                  // Como a curva é no próprio eixo, o que decidiria se fosse pra esquerda ou
                                                                    // direita, seria o reverse.
{
  if (angular != 0) {                                               // Caso angular seja diferente de 0
    forwardSpeed = 0;                                               // Define forwardSpeed como 0
  }
  float linear = (1 - abs(angular));                                // Faz 1 - angular, para saber se é uma curva ou não
                                                                    // Caso angular seja 1, o linear fica 0, é uma curva.
                                                                    // Caso angular seja 0, o linear fica 1, é uma reta.
  
  if(reverse)                                                       // Verifica se reverse é verdadeiro(1)
  {
    linear = -linear;                                               // Caso seja, linear fica negativo, ou seja, reverte.
  }

                                                                    // LeftSpeed
  float leftSpeed = (linear + angular);                             // Caso seja uma curva, linear = 0, angular = 1, leftSpeed = 1
                                                                    // Reverse verdadeiro, linear = 0, angular = 1, leftSpeed = 1
  // Talvez o erro de nao conseguir usar move seja aqui             // Caso seja uma reta, linear = 1, angular = 0, leftSpeed = 1
  // já que o reverse nao está fazendo diferença nas curvas         // Reverse verdadeiro, linear = -1, angular = 0, leftSpeed = -1
                                                                    
                                                                    // RightSpeed
  float rightSpeed  = (linear - angular);                           // Caso seja uma curva, linear = 0, angular = 1, rightSpeed = -1
                                                                    // Reverse verdadeiro, linear = 0, angular = 1, rightSpeed = -1
                                                                    // Caso seja uma reta, linear = 1, angular = 0, rightSpeed = 1
                                                                    // Reverse verdadeiro, linear = -1, angular = 0, rightSpeed = -1

  int leftPWM = map(leftSpeed, -1, 1, -maxPwm, maxPwm);             // Mapear para leftPWM de -1 a 1, para PWM(-255 a 255)
  int rightPWM = map(rightSpeed, -1, 1, -maxPwm, maxPwm);           // Mapear para rightPWM de -1 a 1, para PWM(-255 a 255)

  rightPWM = abs(constrain(rightPWM, -maxPwm, maxPwm));             // Checa se os valores estão dentro de [-maxPwm, maxPwm] e depois atribuí à rightPWM
  leftPWM = abs(constrain(leftPWM, -maxPwm, maxPwm));               // ou leftPWM o valor absoluto dessa checagem.
  /*
  Serial.print(leftPWM);                                            // Debug
  Serial.print("\t");
  Serial.println(rightPWM);
  */
  bool rightForward = leftSpeed > 0;                                // Verifica se leftSpeed é maior que 0, caso seja, rightForward é verdadeiro(1)
  bool leftForward = rightSpeed > 0;                                // Verifica se rightSpeed é maior que 0, caso seja, leftForward é verdadeiro(1)
    
  digitalWrite(rightWheelP1, not rightForward);                     
  digitalWrite(rightWheelP2, rightForward);
  digitalWrite(leftWheelP1, leftForward);
  digitalWrite(leftWheelP2, not leftForward);
  analogWrite(rightWheelPWM, abs(rightPWM)); // Aqui está com o valor absoluto, de uma variável que era atribuida um valor absoluto
  analogWrite(leftWheelPWM, abs(leftPWM)); 
}

//====Início da função stop
void stop()
{
  analogWrite(rightWheelPWM, 0);                                    // Para os dois motores
  analogWrite(leftWheelPWM, 0);
}

//=====Início da função forward
void forward() {
  move(0,forwardSpeed*maxPWM);                                       // Vai para frente acelerando
  forwardSpeed = min(1, forwardSpeed + accelerationRate);
  //Serial.println(forwardSpeed);                                    // Debug
}


//=====Início da função moveLooking
void moveLooking(unsigned int delayToSpin, int movePWM, int lastToSee, bool reverse) {
  unsigned long tempo = millis();                                    // Salva o tempo
  while(millis() - tempo <= delayToSpin)                             // Enquanto o tempo seja menor que delayToSpin
  {
    int side;
    if(anyIR(&side))                                                 // Checa se está vendo alguem
    {
      break;                                                         // Se sim, para a curva
    }
    move(lastToSee, movePWM, reverse);                               // Se não, continua virando
  }
}

//====Início da função spin
void spin(bool right) {
  digitalWrite(rightWheelP1, not right);
  digitalWrite(rightWheelP2, right);
  digitalWrite(leftWheelP1, not right);
  digitalWrite(leftWheelP2, right);
  analogWrite(rightWheelPWM, maxPWM);
  analogWrite(leftWheelPWM, maxPWM);
}
