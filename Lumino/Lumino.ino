/*
Disciplina de Controle de Processos / 2024A
Prof Aline Kafer

Grupo:
Jonathan Bassani
Lucas E. Pandolfo
Maiquel Klein

Projeto 3: Sistema de Controle de Luminosidade para Estufas Agrícolas
*/

#define LED 3
#include <LiquidCrystal.h>                  //Adiciona a biblioteca do display
LiquidCrystal lcd_1(8, 9, 4, 5, 6, 7);      //Botões da shield display 8=reset, 9=enter,  

float LDRint = A5;
float LDRext = A4;
float lumInt = 0;
float lumExt = 0;
int catalogo = 0;
int spUmid = 0;
float setpoint = 0;
float erro = 0;
int pwm;

void setup() {
  lcd_1.begin(16, 2);                          //Define o número de colunas e linhas do display
  lcd_1.setCursor(0, 0);                      //Define o cursor para a coluna 0, linha 0
  lcd_1.print("CONTROLE DE ");
  lcd_1.setCursor(0, 1);                      //Define o cursor para a coluna 0, linha 1
  lcd_1.print("LUMINOSIDADE");
  delay(2000);
  lcd_1.clear();
  Serial.begin(9600);

  //pinMode(LED, OUTPUT);
  pinMode(LDRint, INPUT);
  pinMode(LDRext, INPUT);

  lcd_1.setCursor(0, 0);
  lcd_1.print("<PLANT SELECTOR>");
  lcd_1.setCursor(0, 1);
  lcd_1.print("<Set Point: 000>");
  delay(2000);
}

void cenoura() {
  lcd_1.clear();
  lcd_1.setCursor(0, 0);
  lcd_1.print("<     CASA     >");
  lcd_1.setCursor(0, 1);
  lcd_1.print("<Set Point: 190>");
  setpoint = 190;
  spUmid = 130;
}
void feijao() {
  lcd_1.clear();
  lcd_1.setCursor(0, 0);
  lcd_1.print("<    FEIJAO    >");
  lcd_1.setCursor(0, 1);
  lcd_1.print("<Set Point: 075>");
  setpoint = 75;
  spUmid = 120;
}
void cannabis() {
  lcd_1.clear();
  lcd_1.setCursor(0, 0);
  lcd_1.print("<   CANNABIS   >");
  lcd_1.setCursor(0, 1);
  lcd_1.print("<Set Point: 240>");
  setpoint = 240;
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
  
  lumInt = analogRead(LDRint);
  lumInt = map(lumInt, 0, 1023, 0, 255);
  lumExt = analogRead(LDRext);
  lumExt = map(lumExt, 0, 1023, 0, 255);

void botao(); {
//Serial.println(analogRead(0));                                          //Exibe a leitura do pino analógico A0 no monitor serial
  delay(100);

  if ((analogRead(0)) < 50) {                                           //Se a leitura for menor que 80 chama a função right
    catalogo++;
  } else if ((analogRead(0)) > 410 && (analogRead(0)) < 440) {         //Se a leitura for menor que 600 chama a função left
    catalogo--;
  } else if ((analogRead(0)) > 90 && (analogRead(0)) < 110) {         //Se a leitura for menor que 600 chama a função left
    spUmid++;
  } else if ((analogRead(0)) > 245 && (analogRead(0)) < 265) {         //Se a leitura for menor que 600 chama a função left
    spUmid--;
  }
}

menu();

erro = setpoint - lumInt;
  
  if (erro < 0) {
    pwm = 0;
  } else {
    pwm = erro;
  }
  analogWrite(LED, pwm);

void monitor(); {
  Serial.print("Iluminação Externa: ");
  Serial.println(lumExt);
  Serial.print("Set Point: ");
  Serial.println(setpoint);
  Serial.print("Iluminação Interno: ");
  Serial.println(lumInt);
  Serial.print("Erro: ");
  Serial.println(erro);
  Serial.print("Lampada: ");
  Serial.println(pwm);
  Serial.println( );

  delay(600);
}
}
