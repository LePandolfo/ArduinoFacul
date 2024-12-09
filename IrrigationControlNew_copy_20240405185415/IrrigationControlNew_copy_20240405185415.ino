/*
Disciplina de Controle de Processos / 2024A
Prof Aline Kafer

Grupo:
Jonathan Bassani
Lucas E. Pandolfo
Maiquel Klein
*/

//Definição Pino PMW Arduino
#define PUMP 5
#define PUMPLOW 6

//Configuração inicial
void setup() {
  //Inicia porta serial na taxa de 9600 bits por segundo
  Serial.begin(9600);
}

// Looping infinito que a placa vai ficar processando
void loop() {
  
  int sensorValue1 = analogRead(A0);        //Lê o pino A0 do Arduino, onde está conectado o Sensor 1
  int sensorValue2 = analogRead(A1);        //Lê o pino A1 do Arduino, onde está conectado o Sensor 2
  int setPoint = 500;                       //Set Point para definir até qual nível de umidade queremos manter
  float Kp = 2.2;                           //Controle Proporcional
  float Ki;
  float Kd;
  float P, I, D, PID;
  //float integral = 0;
  float erro = sensorValue1 - setPoint;     //Variavel erro é o erro atual
  int velocidade;
  float pwmV;

if (erro < 5){                               //Se o Erro for Menor ou igual a zero, irá desligar o motor da bomba da água
  //I = integral += Ki * erro;
  velocidade = 0;

}else if (erro > 25){
  P = Kp * erro;
  //I = integral += Ki * erro;
  I = 0;
  D = 0;
  PID = P+I+D;
  velocidade = PID;

}else if (erro < 25 && erro > 5){
  //I = integral += Ki * erro;
  velocidade = 160;                            //Saturação minima
}

  velocidade = constrain(velocidade, 0, 255);
  pwmV = velocidade * 0.04705882;             //Converte valor PWM em Volts

  // print das variaveis uteis:
  Serial.print("Valor Sensor1 = ");
  Serial.print(sensorValue1);
  //Serial.print(" Valor Sensor2 = ");
  //Serial.print(sensorValue2);
  Serial.print(" Erro Atual = ");
  Serial.print(erro);
  Serial.print(" Velocidade Atual = ");
  Serial.print(velocidade);
  Serial.print(" Tensão da Bomba = ");
  Serial.print(pwmV);
  Serial.println(" ");

  digitalWrite(PUMPLOW, LOW);
  analogWrite(PUMP, velocidade);             //Escreve no pino PUMP o valor da velocidade
  
  delay(900);        // delay entre as leituras, para ter uma melhor estabilidade dos valores
}
