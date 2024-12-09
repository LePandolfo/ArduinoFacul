/*
Disciplina de Controle de Processos / 2024A
Prof Aline Kafer

Grupo:
Jonathan Bassani
Lucas E. Pandolfo
Maiquel Klein
*/

#include <LiquidCrystal.h>                  //Adiciona a biblioteca do display
LiquidCrystal lcd_1(8, 9, 4, 5, 6, 7);      //Botões da shield dysplay 8=reset, 9=enter,  
int leds = 3;
float LDRs = A5;
float valorLDRs = 0;
float input = 0;
int ledc = 2;
float LDRc = A2;
float valorLDRc = 0;
float setpoint = 25.0;
int pwm = 0;
int output = 0;
float error = 0;

void setup() {
  Serial.begin(9600);
  pinMode(leds, OUTPUT);
  pinMode(LDRs, INPUT);

  pinMode(ledc, OUTPUT);
  pinMode(LDRc, INPUT);

  pinMode(11, OUTPUT);
  Serial.begin(9600);

  lcd_1.begin(16, 2);
  lcd_1.setCursor(0, 0);
  lcd_1.print("Sistema ligado!");
  delay(2000);
  lcd_1.clear();
  //--------------------//
  lcd_1.setCursor(0, 0);
  lcd_1.print("In:       C");
  lcd_1.setCursor(11, 0);
  lcd_1.print(char(223));  // linha de código imprime o sinal do grau
}
void loop() {
  //Acionamento das lampadas
  //sala

  valorLDRs = analogRead(LDRs);
  if (valorLDRs < 500) {
    digitalWrite(leds, HIGH);
    //digitalWrite(ledc, HIGH);
    lcd_1.setCursor(0, 1);
    lcd_1.print("Sala:ON ");
  }

  if (valorLDRs > 800) {
    digitalWrite(leds, LOW);
   // digitalWrite(ledc, LOW);
    lcd_1.setCursor(0, 1);
    lcd_1.print("Sala:OFF");
  }
  //cozinha

  valorLDRc = analogRead(LDRc);
  if (valorLDRc < 500) {
    digitalWrite(ledc, HIGH);
    lcd_1.setCursor(9, 1);
    lcd_1.print("Coz:ON ");
  }

  if (valorLDRc > 800) {
    digitalWrite(ledc, LOW);
    lcd_1.setCursor(9, 1);
    lcd_1.print("Coz:OFF");
  }


  //----------------------------------------//

  //Ventilação

  int adc = analogRead(A3);
  
  input = adc * 0.4887;  //leitura da variável de processo (sensor)

  // Cálculo do erro
  error = input - setpoint;
 Serial.println(error);
 if (error < 0)
  {
  pwm = 0;

  }
  if (error < 0.5 && error >= 0)
  {
  pwm = 41;

  }
  
  if (error < 1 && error >= 0.5)
  {
  pwm = 81;
  }
   
  if (error < 1.5 && error >= 1)
  {
  pwm = 114;
  }
   if (error < 2 && error >= 1.5)
  {
  pwm = 140;
 
  }
   if (error < 2.5 && error >= 2)
  {
  pwm = 163;
  }
   if (error < 3 && error >= 2.5)
  {
  pwm = 181;

  }
  
  if (error < 3.5 && error >= 3)
  {
  pwm = 199;
  }
   
  if (error < 4 && error >= 3.5)
  {
  pwm = 214;
  }
   if (error < 4.5 && error >= 4)
  {
  pwm = 227;
 
  }
   if (error < 5 && error >= 4.5)
  {
  pwm = 242;
  }
   if (error < 5.5 && error >= 5)
  {
  pwm = 255;
  }
  
//LCD
Serial.print("Error:");
Serial.println(error);
Serial.print("PWM:");
Serial.println(pwm);
Serial.print("Input:");
Serial.println(input);
digitalWrite(11, pwm);
lcd_1.setCursor(5, 0);
lcd_1.print(input);
lcd_1.print("");
delay(1000);
}
