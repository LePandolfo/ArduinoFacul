#include <Wire.h>
#include <PID_v1.h>

//Inicializa o DHT22
#include <Adafruit_Sensor.h>
#include <DHT_U.h>
#include <DHT.h>
#define DHTTYPE DHT22


//Pinagem
#define DHTPIN 2      // Pino do Sensor DHT22
#define LAMP_PIN 5  // PWM Lâmpada (L298N IN1)
#define COOLER_PIN 10   // PWM Cooler (L298N IN3)

DHT_Unified dht(DHTPIN, DHTTYPE);

//Variáveis
double temperatura;
double umidade;
int coolerPWM;
int lampPWM;
int lampPWMout = 0;
int coolerPWMout = 0;

double Input, Output;
double Setpoint = 70;
double Kp = 45;
double Ki = Kp/2;
double Kd = Kp * 0.05;
/*
const float K[4] = {80, 8, 70, 5};
float theta;
float omega = 0.0;
float previousTheta = 0.0;
float deltaT = 0.0;
float time = 0.0;
float previousTime = 0.0;
*/
PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);

uint32_t delayMS;

void setup() {
  Serial.begin(9600);
  myPID.SetMode(AUTOMATIC);
  dht.begin();
  pinMode(LAMP_PIN, OUTPUT);
  pinMode(COOLER_PIN, OUTPUT);

  sensor_t sensorT, sensorH;

  dht.humidity().getSensor(&sensorH);
  dht.temperature().getSensor(&sensorT);

  delayMS = sensorT.min_delay / 1000;

}

void loop() {
  delay(delayMS);

  sensors_event_t tempEvent, humEvent;

  // Leitura do DHT22
  temperatura = dht.temperature().getEvent(&tempEvent);
  umidade = dht.humidity().getEvent(&humEvent);

  // Controle do cooler
  if (isnan(umidade) || isnan(temperatura)) {
    Serial.println("Falha ao ler do sensor DHT!");
    return;
  } else {
    //theta = humEvent.relative_humidity;
    //omega = humEvent.temperature;
    Input = humEvent.relative_humidity;
    myPID.Compute();

    coolerPWM = 255 - Output;
    lampPWM = 255 - Output;
  }
/*
  // Derivada da posição (taxa de variação da posição no tempo)
  previousTime = time;
  time = millis();
  deltaT = (time - previousTime);
  previousTheta = theta;
  omega = (theta - previousTheta) / deltaT;
  
  // Realimentação de estado
  lampPWM = K[0] * theta - K[1] * omega;
  coolerPWM = K[2] * theta - K[3] * omega;
  lampPWMout = lampPWM ;
  coolerPWMout = coolerPWM ;
  
  if (humEvent.relative_humidity > 80){
    coolerPWMout = 255;
    lampPWMout = 255;
  }else if (humEvent.relative_humidity < 80){
    coolerPWMout = 0;
    lampPWMout = 0;
    

  }
*/
  // Serial Print
  Serial.print(F("Humidade: "));
  Serial.print(humEvent.relative_humidity);
  Serial.println("%");
  Serial.print(F("Temperatura: "));
  Serial.print(tempEvent.temperature);
  Serial.println("ºC");
  Serial.print(F("PMW Lâmpada: "));
  //Serial.println(lampPWMout);
  Serial.println(lampPWM);
  Serial.print(F("PMW Ventilador: "));
  //Serial.println(coolerPWMout);
  Serial.println(coolerPWM);
  Serial.print(F("Inp: "));
  Serial.println(Input);
  Serial.print(F("Outp: "));
  Serial.println(Output);

  //Acionamento PWM
  //analogWrite(LAMP_PIN, constrain(lampPWMout,0,255));
  //analogWrite(COOLER_PIN, constrain(coolerPWMout,0,255));
  analogWrite(LAMP_PIN, constrain(lampPWM,0,255));
  analogWrite(COOLER_PIN, constrain(coolerPWM,0,255));

}