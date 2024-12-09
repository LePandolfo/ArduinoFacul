/*
Disciplina de Controle de Processos / 2024A
Prof Aline Kafer

Grupo:
Jonathan Bassani
Lucas E. Pandolfo
Maiquel Klein

Projeto 5: Sistema de Controle de Alinhamento para Carrinho Seguidor de Linha
*/


#include <Wire.h>
#include <Arduino.h>
#include <SD.h>

#define OUT_M_ESQ 10
#define OUT_M_DIR 9

//variáveis necessárias para o controle da velocidade
int P, D, I, previousError, PIDvalue, error;
int lsp, rsp;                                     // left speed (velocidade da esquerda) e right speed (velocidade da direita)
int lfspeed = 200;                                //limit fast speed (velocidade rápida limite - o PWM aceita até 255)
int velocidade = 200;

//inicialização das variáveis de controle
float Kp = 7;
float Kd = 7;
float Ki = 0;

//valores usados para a calibração do robô
int minValues[6], maxValues[6], threshold[6];

void PID() {
  int error = analogRead(2) - analogRead(4);

  P = error;
  I = I + error;
  D = error - previousError;

  PIDvalue = (Kp * P) + (Ki * I) + (Kd * D);
  previousError = error;

  lsp = lfspeed - PIDvalue;
  rsp = lfspeed + PIDvalue;

  if (lsp > velocidade) {
    lsp = velocidade;
  }
  if (lsp < 0) {
    lsp = 0;
  }
  if (rsp > velocidade) {
    rsp = velocidade;
  }
  if (rsp < 0) {
    rsp = 0;
  }

}

void linefollow()
{
  
  PID();

  analogWrite(OUT_M_ESQ, lsp);
  analogWrite(OUT_M_DIR, rsp);

}

void calibrate()
{
  for ( int i = 1; i < 6; i++)
  {
    minValues[i] = analogRead(i);
    maxValues[i] = analogRead(i);
  }

  for (int i = 0; i < 3000; i++)
  {
    analogWrite(OUT_M_ESQ,200);
    analogWrite(OUT_M_DIR,0);

    for ( int i = 1; i < 6; i++)
    {
      if (analogRead(i) < minValues[i])
      {
        minValues[i] = analogRead(i);
      }
      if (analogRead(i) > maxValues[i])
      {
        maxValues[i] = analogRead(i);
      }
    }
  }

  for ( int i = 1; i < 6; i++)
  {
    threshold[i] = (minValues[i] + maxValues[i]) / 2;
    Serial.print(threshold[i]);
    Serial.print("   ");
  }
  Serial.println();
  
  analogWrite(OUT_M_ESQ,0);
  analogWrite(OUT_M_DIR,0);
}

void setup() {

  Serial.begin(9600);
  pinMode(11, INPUT_PULLUP);
  pinMode(12, INPUT_PULLUP);

}

void loop() {
  // os pinos 11 e 12 são, respectivamente, o inicio da calibração e o início da operação do carrinho
 //while (digitalRead(11)) {}
  delay(1000);
  calibrate();
 //while (digitalRead(12)) {}
  delay(1000);

 //rotina principal
  while (1)
  {
      linefollow();
    }
  }
