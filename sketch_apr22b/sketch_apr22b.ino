const int pinoSensor = A0;

void setup() {
  Serial.begin(115200);
}

void loop() {
  int leitura = analogRead(pinoSensor);

  Serial.print("Valor do sensor: ");
  Serial.println(leitura);

  delay(200);
}
