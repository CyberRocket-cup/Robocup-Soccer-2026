const int pinoSensor = A0;

// 👉 SEUS VALORES (mantidos)
const int LIMIAR_VERDE  = 977;
const int LIMIAR_BRANCO = 824;

void setup() {
  Serial.begin(115200);
}

void loop() {
  int leitura = analogRead(pinoSensor);

  Serial.print("Valor: ");
  Serial.print(leitura);
  Serial.print(" -> ");

  // 🔁 LÓGICA INVERTIDA
  if (leitura >= LIMIAR_VERDE) {
    Serial.println("VERDE");   // valores altos = VERDE
  } 
  else if (leitura <= LIMIAR_BRANCO) {
    Serial.println("BRANCO");  // valores baixos = BRANCO
  } 
  else {
    Serial.println("INDEFINIDO");
  }

  delay(200);
}
