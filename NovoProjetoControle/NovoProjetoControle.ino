int fitaLed = 3;
int ldrIn = A5;
float lumInt;
float setpoint;
float erro;
float pwm;

void setup() {
  pinMode(ldrIn, INPUT);
  pinMode(fitaLed, OUTPUT);
  Serial.begin(9600);

}

void loop() {
  setpoint = 220;
  lumInt = analogRead(ldrIn);
  lumInt = map(lumInt, 0, 1023, 0, 254);

  erro = setpoint - lumInt;
    if (erro < 0) {
      pwm = 0;
    }else{
      pwm = erro;
    }
    analogWrite(fitaLed, pwm);
    Serial.print("Luminosidade: ");
    Serial.println(lumInt);
    Serial.print("Setpoint: ");
    Serial.println(setpoint);
    Serial.print("PWM LED: ");
    Serial.println(pwm);
  delay(600);
}