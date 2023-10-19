const int pin25out = 25;
const int pin33out = 33;
const int pin32out = 32;


void setup() {
  // Define o pino 25 como SAIDA
  pinMode(pin25out,OUTPUT);
  pinMode(pin33out,OUTPUT);
  pinMode(pin32out,OUTPUT);


  // Inicializa a porta serial de com. com o ESP32
  Serial.begin(115200);
  Serial.println("Iniciando a serial");
}


void loop() {
  digitalWrite(pin25out, LOW);
  digitalWrite(pin33out, LOW);
  digitalWrite(pin32out, LOW);

  
  digitalWrite(pin25out, HIGH);
  delay(1000);
  digitalWrite(pin25out, LOW);


  digitalWrite(pin33out, HIGH);
  delay(1000);
  digitalWrite(pin33out, LOW);

  digitalWrite(pin32out, HIGH);
  delay(1000);
  digitalWrite(pin32out, LOW);

}