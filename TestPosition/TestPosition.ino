double angle;
double offset = 0;
double calib = 138;
double tempo = 0;

int valorAtual = 0;
int valorAnterior = 0;

void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  int sensorValue = analogRead(A0);
 

  map (sensorValue, 0, 1023, 0, 269);
  angle = map (sensorValue, 0, 1023, 0, 269);
  angle = angle + offset - calib;
  Serial.print("Angulo: ");
  Serial.println(angle);
  Serial.println("_________________");
  Serial.print("Valor Sensor: ");
  Serial.println(sensorValue);
  Serial.println("_________________");
  delay(100);  // delay in between reads for stability


}