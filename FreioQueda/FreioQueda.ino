/*
Disciplina de Controle de Processos 2 / 2024B
Prof Aline Kafer

Grupo:
Lucas E. Pandolfo
Nata Vargas
Rafael B. Taufer
Thiago Mors

Projeto 3: Freio de Queda
*/

/*
// Definições das matrizes do sistema
const float m = 0.0;          // Massa do "Carrinho"
const float h = 0.54;         // Altura da Queda
const float g = 9.81;         // Gravidade
const float fP = m * h * g;    // Força Peso
const float v;                //Tensão Motor
const float t;                //Constante de Toque do Motor
const float fT = v * t;       //Força Torque
const float eq = (fP ==fT)    //Equilíbrio
*/

//Definição Pinos
#define safe 10
#define pintrigger 12
#define pinecho 13
#include <Servo.h>
Servo helice;

//Definição variáveis
int botao;
int rotacao;
int fHelice = 0;
float altura = 0.0;
float duracao = 0.0;
int valueH = 0;
int erro = 0;
int setPoint = 15;
int startK = 180;
float trigger = 0.0;
float echo = 0.0;

// Ganhos do controlador
const float K[2] = {1, 1};

// Estados do sistema
float theta = 0.0; // Altura do Carrinho (posição)
float omega = 0.0; // Velocidade do Carrinho
static float previousTheta = 0.0;

//Variaveis de tempo
float time = 0.0;
float deltaT = 0.0;
static float previousTime = 0.0;

void setup() {
  pinMode(safe,INPUT_PULLUP);
  Serial.begin(115200);
  helice.attach(9,900,2000);
  helice.write(0);

  delay(10000);

  pinMode(pintrigger,OUTPUT);
	pinMode(pinecho,INPUT);
	trigger = pintrigger;
	echo = pinecho;

}

void loop() {
  digitalWrite(trigger,LOW);
	delayMicroseconds(2);
	digitalWrite(trigger,HIGH);
	delayMicroseconds(10);
	digitalWrite(trigger,LOW);

  duracao = pulseIn(echo,HIGH);
 	altura = duracao * (0.039/2);
  theta = map(altura, 0, 56, 0, 255); // Ajuste Altura > PWM
  valueH = altura * 4.75;
  erro = valueH - setPoint;
  

  // Velocidade = derivada da posição (taxa de variação da posição no tempo)
  previousTime = time;
  time = millis();
  deltaT = (time - previousTime);
  previousTheta = theta;
  omega = (theta - previousTheta) / deltaT;


  // Realimentação de estado
  fHelice = -K[0] * theta - K[1] * omega;

  botao = digitalRead(safe);
  


  if (erro > startK){
    fHelice = 0;                                              //Comentar depois que fizer o controle
    helice.write(fHelice);

  }else{
    fHelice = 100;                                            //Comentar depois que fizer o controle
    
    if (botao == 1){
      helice.write(0);
    }else{
      helice.write(fHelice);
    }
  }


  Serial.println("      ");
  Serial.print(altura);
  Serial.print(" cm  |");
  Serial.print(theta);
  Serial.print(" AlturaPWM  |");
  Serial.print(erro);
  Serial.print(" erroPWM  |");
  Serial.print(fHelice);
  Serial.print(" forçaMotor  ");
  Serial.println(botao);
  
}
