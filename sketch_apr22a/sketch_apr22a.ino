// Pinos
const int pinoSensor = A0;

// Variáveis de calibração
int limiteBranco = 0;
int limiteVerde = 0;
int limiar = 0; // ponto de decisão automático

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.println("--- MODO DE CALIBRACAO ---");

  // Calibração BRANCO
  Serial.println("Coloque no BRANCO...");
  piscarLED(3);
  limiteBranco = fazerMediaFiltrada();
  Serial.print("Branco: "); Serial.println(limiteBranco);

  delay(3000);

  // Calibração VERDE
  Serial.println("Coloque no VERDE...");
  piscarLED(3);
  limiteVerde = fazerMediaFiltrada();
  Serial.print("Verde: "); Serial.println(limiteVerde);

  // Calcula limiar automaticamente (ponto médio)
  limiar = (limiteBranco + limiteVerde) / 2;

  Serial.print("Limiar definido: ");
  Serial.println(limiar);

  Serial.println("--- CALIBRACAO OK ---");
}

void loop() {
  int leitura = fazerMediaFiltrada();

  Serial.print("Leitura: ");
  Serial.print(leitura);
  Serial.print(" -> ");

  if (leitura > limiar) {
    Serial.println("BRANCO");
  } else {
    Serial.println("VERDE");
  }

  delay(200);
}

// Média + filtro simples contra ruído
int fazerMediaFiltrada() {
  const int amostras = 30;
  int valores[amostras];

  for (int i = 0; i < amostras; i++) {
    valores[i] = analogRead(pinoSensor);
    delay(2);
  }

  // Ordena (bubble sort simples)
  for (int i = 0; i < amostras - 1; i++) {
    for (int j = i + 1; j < amostras; j++) {
      if (valores[j] < valores[i]) {
        int temp = valores[i];
        valores[i] = valores[j];
        valores[j] = temp;
      }
    }
  }

  // Remove extremos (outliers)
  long soma = 0;
  for (int i = 5; i < amostras - 5; i++) {
    soma += valores[i];
  }

  return soma / (amostras - 10);
}

// Feedback visual melhor
void piscarLED(int vezes) {
  for (int i = 0; i < vezes; i++) {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(300);
    digitalWrite(LED_BUILTIN, LOW);
    delay(300);
  }
}
