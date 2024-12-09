/*
Disciplina de Controle de Processos / 2024A
Prof Aline Kafer

Grupo:
Jonathan Bassani
Lucas E. Pandolfo
Maiquel Klein

Projeto 3: Sistema de Controle de Luminosidade e Umidade para Estufas Agrícolas
*/

#include <LiquidCrystal.h>                  //Adiciona a biblioteca do display
LiquidCrystal lcd_1(8, 9, 4, 5, 6, 7);      //Botões da shield display 8=reset, 9=enter,
int catalogo = 0;

//Pinos Luminosidade
float LDRint = A5;
float LDRext = A4;
int LED = 3;

//Pinos Umidade
int SensUmid1 = A0;
int SensUmid2 = A1;
int PUMP = 11;

//Variáveis Luminosaidade
float lumInt = 0;
float lumExt = 0;
int spLum = 0;
int spLumC = 120;
int spLumF = 80;
int spLumM = 250;
int spLumVar = 0;
float Lerro = 0;
int Lpwm = 0;

//Variáveis Umidade
int Umid1 = 0;                               //Valor do Sensor 1
int Umid2 = 0;                               //Valor do Sensor 2
int spUmid = 0;                              //Set Point para definir até qual nível de umidade queremos manter
int UsatMaxV = 24;                           //Valor de Saturação máxima da Bomba
int UsatMinV = 7.5;                          //Valor de Saturação minima da Bomba
float UKp = 5;                               //Controlador P que é a proporção entre a escala do PWM (255) e o range de operação da Bomba
float Uerro = 0;                             //Variavel erro é o erro atual, que referenciará a rampa de velocidade do motor da bomba da água
int UvelPWM = 0;                             //Variavel da velocidade em valor PWM
float UvelV = 0;                             //Variavel da velocidade em Volts

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(LDRint, INPUT);
  pinMode(LDRext, INPUT);

  pinMode(PUMP, OUTPUT);
  pinMode(SensUmid1, INPUT);
  pinMode(SensUmid2, INPUT);

  lcd_1.begin(16, 2);                          //Define o número de colunas e linhas do display
  lcd_1.setCursor(0, 0);                      //Define o cursor para a coluna 0, linha 0
  lcd_1.print("CONTROLE DE ");
  lcd_1.setCursor(0, 1);                      //Define o cursor para a coluna 0, linha 1
  lcd_1.print("LUMINOSIDADE");
  delay(3000);
  lcd_1.clear();
  Serial.begin(9600);

  lcd_1.setCursor(0, 0);
  lcd_1.print("<PLANT SELECTOR>");
  lcd_1.setCursor(0, 1);
  lcd_1.print("<Set Point: 000>");
  delay(3000);

}

void cenoura() {
  lcd_1.clear();
  lcd_1.setCursor(0, 0);
  lcd_1.print("<   CENOURAS   >");
  lcd_1.setCursor(0, 1);
  lcd_1.print("<Set Point: ");
  lcd_1.setCursor(12, 1);
  lcd_1.print(spLum);
  lcd_1.setCursor(15, 1);
  lcd_1.print(">");
  spLum = spLumC + spLumVar;
  spUmid = 130;
}
void feijao() {
  lcd_1.clear();
  lcd_1.setCursor(0, 0);
  lcd_1.print("<    FEIJAO    >");
  lcd_1.setCursor(0, 1);
  lcd_1.print("<Set Point: ");
  lcd_1.setCursor(12, 1);
  lcd_1.print(spLum);
  lcd_1.setCursor(15, 1);
  lcd_1.print(">");
  spLum = spLumF + spLumVar;
  spUmid = 120;
}
void cannabis() {
  lcd_1.clear();
  lcd_1.setCursor(0, 0);
  lcd_1.print("<   CANNABIS   >");
  lcd_1.setCursor(0, 1);
  lcd_1.print("<Set Point: ");
  lcd_1.setCursor(12, 1);
  lcd_1.print(spLum);
  lcd_1.setCursor(15, 1);
  lcd_1.print(">");
  spLum = spLumM + spLumVar;
  spUmid = 125;
}

void menu() {
  if(catalogo == 0){
    cenoura();
  } else if(catalogo == 1){
    feijao();
  } else if(catalogo == 2){
    cannabis();
  } else if (catalogo == 3){
    catalogo = 2;
  }  else if (catalogo == -1){
    catalogo = 0;
  }
}

void loop() {
  //
  lumInt = analogRead(LDRint);
  lumInt = map(lumInt, 0, 1023, 0, 255);
  lumExt = analogRead(LDRext);
  lumExt = map(lumExt, 0, 1023, 0, 255);

  Lerro = spLum - lumInt;
  
  if (Lerro < 0) {
    Lpwm = 0;
  } else {
    Lpwm = Lerro;
  }
  analogWrite(LED, Lpwm);

  //
  Umid1 = analogRead(SensUmid1);
  Umid1 = map(lumInt, 0, 1023, 0, 255);
  Umid2 = analogRead(SensUmid2);
  Umid2 = map(lumExt, 0, 1023, 0, 255);
  
  Uerro = Umid1 - spUmid;
  UvelV = UvelPWM * 0.09411765;

  analogWrite(PUMP, UvelPWM);

void botao(); {
  Serial.print("Valor Botão:");
  Serial.println(analogRead(0));                                          //Exibe a leitura do pino analógico A0 no monitor serial
  delay(100);

  if ((analogRead(0)) < 10) {                                           //Se a leitura for menor que 80 chama a função right
    catalogo++;
  } else if ((analogRead(0)) > 400 && (analogRead(0)) < 420) {         //Se a leitura for menor que 600 chama a função left
    catalogo--;
  } else if ((analogRead(0)) > 90 && (analogRead(0)) < 110) {         //Se a leitura for menor que 600 chama a função left
    spLumVar++;
  } else if ((analogRead(0)) > 245 && (analogRead(0)) < 265) {         //Se a leitura for menor que 600 chama a função left
    spLumVar--;
  }
}

menu();

void monitor(); {
  //Serial.print("Planta: ");
  //Serial.println(catalogo);
  //Serial.println( );

  //Informações de Iluminação no Monitor Serial
  Serial.println("Iluminação");
  //Serial.print("LDR Ext: ");
  //Serial.println(lumExt);
  Serial.print("Set Point: ");
  Serial.println(spLum);
  Serial.print("LDR Int: ");
  Serial.println(lumInt);
  Serial.print("Erro: ");
  Serial.println(Lerro);
  Serial.print("LED: ");
  Serial.println(Lpwm);
  Serial.println( );

  //Informações de Umidade no Monitor Serial
  //Serial.println("Umidade");
  //Serial.print("Valor Sensor1 = ");
  //Serial.println(Umid1);
  //Serial.print(" Valor Sensor2 = ");
  //Serial.println(Umid2);
  //Serial.print("Set Point: ");
  //Serial.println(spUmid);
  //Serial.print(" Erro Atual = ");
  //Serial.println(Uerro);
  //Serial.print(" Velocidade Atual = ");
  //Serial.println(UvelPWM);
  //Serial.print(" Tensão da Bomba = ");
  //Serial.println(UvelV);
  Serial.println(" ");


  delay(600);
}

}
