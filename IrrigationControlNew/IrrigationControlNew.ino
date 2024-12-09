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
  //Inicia porta serial na taxa de 9600 bits por segundo
  Serial.begin(9600);
}

// Looping infinito que a placa vai ficar processando
void loop() {
  
  int sensorValue1 = analogRead(A0);        //Lê o pino A0 do Arduino, onde está conectado o Sensor 1
  int sensorValue2 = analogRead(A1);        //Lê o pino A1 do Arduino, onde está conectado o Sensor 2
  int velocidade;
  int setPoint = 500;                       //Set Point para definir até qual nível de umidade queremos manter
  int sensorMax = 900;                      //Valor de Saturação máxima do Sensor
  float erroMax = sensorMax - setPoint;     //erroMax é a variavel que pega a diferença entre o setPoint escolhido, e a saturação do sensor, para possamos calcular proporcionalmente a velocidade da bomba de água
  float P = 255 / erroMax;                  //Controlador P que é a proporção entre a escala do PWM (255) e a diferença máxima de leitura com o nosso setPoint
  float erro = sensorValue1 - setPoint;     //Variavel erro é o erro atual, que referenciará a rampa de velocidade do motor da bomba da água
  float pwmV = velocidade * 0.09411765;
  int saturaMin = velocidade;

  // print das variaveis uteis:
  Serial.print("Valor Sensor1 = ");
  Serial.print(sensorValue1);
  Serial.print(" Valor Sensor2 = ");
  Serial.print(sensorValue2);
  Serial.print(" Erro Atual = ");
  Serial.print(erro);
  Serial.print(" Velocidade Atual = ");
  Serial.print(velocidade);
  Serial.print(" Tensão da Bomba = ");
  Serial.print(pwmV);
  Serial.println(" ");

if (erro < 5){                               //Se o Erro for Menor ou igual a zero, irá desligar o motor da bomba da água
  velocidade = 0;
}else if (erro > 10 && saturaMin < 80){
  velocidade = 80;                           //Se for maior que 10, então a velocidade será o multiplo do erro pelo controlador P
}else if (erro > 10){
  velocidade = erro * P;
}

  analogWrite(OUT_M, velocidade);
  
  delay(600);        // delay entre as leituras, para ter uma melhor estabilidade dos valores
}
