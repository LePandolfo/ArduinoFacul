/*
Disciplina de Controle de Processos 2 / 2024B
Prof Aline Kafer

Grupo:
Lucas E. Pandolfo
Nata Vargas
Rafael B. Taufer
Thiago Mors

Projeto 2: Pendulo
*/

#include <Wire.h>

// Definições das matrizes do sistema
const float m = 0.4; // Massa da haste
const float L = 0.38; // Comprimento da haste
const float g = 9.81; // Gravidade
const float I = m * L * L / 3; // Momento de inércia do pêndulo

// Ganhos do controlador
const float K[2] = {12.0, 1.2};

// Estados do sistema
float theta = 0.0; // Ângulo da haste
float omega = 0.0; // Velocidade angular da haste
static float previousTheta = 0.0;

//Variaveis de tempo
float time = 0.0;
float deltaT = 0.0;
static float previousTime = 0.0;

// Entradas do sistema
float u = 0.0; // Torque aplicado

// Pinos
const int potPin = A0; // Pino do potenciômetro
const int motorPin1 = 11; // Pino1 do motor (L298N IN1)
const int motorPin2 = 9; // Pino2 do motor (L298N IN2)
//const int enablePin = 11; // Pino de habilitação do motor (L298N ENA)

void setup() {
  Serial.begin(9600);
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
}

void loop() {
  // Leitura do potenciômetro (ângulo da haste)
  int potValue = analogRead(potPin);
  
  // Conversão da leitura do potenciômetro para ângulo
  theta = map(potValue, 0, 1023, -180, 180); // Ajuste conforme necessário
  
  // Vel angular = derivada da posição (taxa de variação da posição no tempo)
  previousTime = time;
  time = millis();
  deltaT = (time - previousTime);
  previousTheta = theta;
  omega = (theta - previousTheta) / deltaT;
  
  // Realimentação de estado
  u = -K[0] * theta - K[1] * omega;
  
  // Controle do motor
  if (u > 0) {
   analogWrite(motorPin1, constrain(u, 0, 255));
   if(u < 5){u = 25;}
   analogWrite(motorPin2, 0);
  } else if (u < 0) {
    analogWrite(motorPin1, 0);
    if(u > -5){u = 25;}
    analogWrite(motorPin2, constrain(-u, 0, 255));
  } else {
    analogWrite(motorPin1, 0);
    analogWrite(motorPin2, 0);
  }


  // Serial Print
  Serial.print("Theta: ");
  Serial.print(theta);
  Serial.print(" Omega: ");
  Serial.print(omega);
  Serial.print(" Torque: ");
  Serial.println(u);
  //Serial.print(" deltaT: ");
  //Serial.print(deltaT);
  //Serial.print(" Time: ");
  //Serial.println(time);

}