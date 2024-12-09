/*
Disciplina de Controle de Processos / 2024A
Prof Aline Kafer

Grupo:
Jonathan Bassani
Lucas E. Pandolfo
Maiquel Klein

Projeto 2: Sistema de Controle de Nível
*/

#define MOTOR 6
double setpoint = 400;
double sensor =400;
double pwm;
double erro;
double erroAnt = 0;
double integral = 0;

double Kp = 4.8;
double Ki = 0.48;
double Kd = 0.048;
double P = 0;
double I = 0;
double D = 0;

void setup() {
  Serial.begin(9600);
  pinMode(MOTOR, OUTPUT);
}

void loop() {
  int sensorValue1 = analogRead(A3);
  sensor = sensorValue1;

  erro = setpoint - sensor;
  P = Kp * erro;
  if (pwm < 254 && erro < 54) {
    I = integral += Ki * erro;
    D = Kd * (erro - erroAnt);
  }  
  
  erroAnt = erro;
  pwm = P + I + D;
  pwm = constrain(pwm, 0, 255);
  analogWrite(MOTOR, pwm);

  //Monitor
  Serial.print("Valor sensor 1: ");
  Serial.println(sensorValue1);
  Serial.print("Erro: ");
  Serial.println(erro);
  Serial.print("Velocidade: ");
  Serial.println(pwm);
  Serial.print("Proporcional: ");
  Serial.println(P);
  Serial.print("Integrador: ");
  Serial.println(I);
  Serial.print("Derivador: ");
  Serial.println(D);
  Serial.println("-----------------");

  delay(600);
}
