/*
Disciplina de Controle de Processos / 2024A
Prof Aline Kafer

Grupo:
Jonathan Bassani
Lucas E. Pandolfo
Maiquel Klein
*/

//Definição Pino PMW Arduino
#define OUT_M 11


//Configuração inicial
void setup() {

Serial.begin(9600);

}

// Looping infinito que a placa vai ficar processando
void loop() {
  int sensorValue1 = 0;                         //Lê o pino A0 do Arduino, onde está conectado o Sensor 1
  int sensorValue2 = 0;                         //Lê o pino A1 do Arduino, onde está conectado o Sensor 2
  int setPoint = 125;                           //Set Point para definir até qual nível de umidade queremos manter
  int saturMaxV = 24;                           //Valor de Saturação máxima da Bomba
  int saturMinV = 7.5;                          //Valor de Saturação minima da Bomba
  float P = 5;                                  //Controlador P que é a proporção entre a escala do PWM (255) e o range de operação da Bomba
  float erro = 0;                               //Variavel erro é o erro atual, que referenciará a rampa de velocidade do motor da bomba da água
  int velPWM = 0;                               //Variavel da velocidade em valor PWM
  float velV = 0;                               //Variavel da velocidade em Volts

  sensorValue1 = analogRead(A0);
  sensorValue1 = map(sensorValue1, 0, 1023, 0, 255);
  sensorValue2 = analogRead(A1);
  sensorValue2 = map(sensorValue2, 0, 1023, 0, 255);
  erro = sensorValue1 - setPoint;
  velV = velPWM * 0.09411765;


  // print das variaveis uteis:
  Serial.print("Valor Sensor1 = ");
  Serial.print(sensorValue1);
  Serial.print(" Valor Sensor2 = ");
  Serial.print(sensorValue2);
  Serial.print(" Erro Atual = ");
  Serial.print(erro);
  Serial.print(" Velocidade Atual = ");
  Serial.print(velPWM);
  Serial.print(" Tensão da Bomba = ");
  Serial.print(velV);
  Serial.println(" ");

  
  analogWrite(OUT_M, velPWM);                     //Escreve no pino "OUT_M" o valor da velocidade
  
  delay(600);                                     // delay entre as leituras, para ter uma melhor estabilidade dos valores
}
