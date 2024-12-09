#define AMP_MAX 3.0
#define RANGE 30.0
#define SAMPLE (RANGE+1)/AMP_MAX

#include <Servo.h>
Servo garra;
//double setpoint=4.14;
double erro;
double Kp=1;
int vel=100;
float corrente;
int pos = 0;
void setup()
{
  garra.attach(9);
  Serial.begin(9600);
  pinMode(corrente, INPUT);
}
void loop()
{
  //while(corrente < setpoint){
    for(pos = 0; pos < 23;pos += 1){
      garra.write(pos);
      delay(vel);
      Serial.print("Posição: ");
      Serial.println(pos);
      corrente = (analogRead(A0)-RANGE)/SAMPLE;
      Serial.print("Corrente: ");
      Serial.println(corrente);
  }
    for(pos = 23; pos >= 1;pos -= 1){
      garra.write(pos);
      delay(vel);
      Serial.print("Posição: ");
      Serial.println(pos);
      corrente = (analogRead(A0)-RANGE)/SAMPLE;
      Serial.print("Corrente: ");
      Serial.println(corrente);
    }
    vel = 100;
    //erro = setpoint - corrente;
    //vel = Kp*erro;
//}
}