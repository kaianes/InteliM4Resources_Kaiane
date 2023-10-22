// C++ code
//

int porta = 13;

void setup()
{
  pinMode(porta, OUTPUT);
}

void loop()
{
  digitalWrite(porta, HIGH);
  delay(500); // Wait for 500 millisecond(s)
  digitalWrite(porta, LOW);
  delay(500); // Wait for 500 millisecond(s)
}