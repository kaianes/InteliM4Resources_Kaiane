// Código do jogo "Genius"


/*

A protoboard começa com os leds piscando, somente ao apertar o botão de reset o jogo inicia.

O botão de reset só funciona se o jogador errar a sequência

O jogo termina quando o jogador finalizar corretamente as 5 fases/sequências do jogo.

*/



// Define os pinos dos LEDs e do buzzer
const int LED1 = 16;
const int LED2 = 17;
const int LED3 = 21;
const int LED4 = 22;
const int BUZZER = 14; // Pino do buzzer

// Define os pinos dos botões
const int BOTAO1 = 27;
const int BOTAO2 = 26;
const int BOTAO3 = 25;
const int BOTAO4 = 33;
const int BOTAORESET = 35;

// Define o número máximo de níveis do jogo
const int MAX_LEVEL = 5;

// Arrays para armazenar os pinos dos LEDs e botões
int leds[4] = {LED1, LED2, LED3, LED4};
int botoes[4] = {BOTAO1, BOTAO2, BOTAO3, BOTAO4};

// Arrays para armazenar as sequências do jogo
int sequencia[MAX_LEVEL];
int player_sequence[MAX_LEVEL];

// Variáveis para controlar o estado do jogo
int nivel = 0;
int velocidade = 1000;

// Frequências dos tons (C, D, E, F)
const int tones[] = {262, 294, 330, 349};

// Função para configurar os pinos
// Faz um "for" e percorre cada um dos itens definindo se é input ou output
void configurarPinos() {
  for (int i = 0; i < 4; i++) {
    pinMode(leds[i], OUTPUT);
    pinMode(botoes[i], INPUT_PULLUP);
  }
  pinMode(BOTAORESET, INPUT_PULLUP);
  pinMode(BUZZER, OUTPUT);
}

/*INPUT_PULLUP: Quando você configura um pino como INPUT_PULLUP, ele possui uma resistência de pull-up interna. 
Isso significa que, quando o botão não está pressionado, o pino é automaticamente mantido em nível HIGH (pelo resistor pull-up interno). 
Quando o botão é pressionado, ele é conectado ao terra (GND), alterando o nível do pino para LOW. Isso ajuda a evitar leituras flutuantes, 
pois o pino está sempre em um estado definido (HIGH quando não pressionado).
PARA RESOLVER BOUCING DE BOTÕES SEM CPACITORES
*/


// Função para iniciar o jogo
// Aqui é definida a ordem aleatória da sequência, enquanto for menor que o nível maximo (5)
//Aqui a "sequência" é usada na função "mostrarSequencia"
void iniciarJogo() {
  nivel = 1;
  randomSeed(analogRead(0));
  for (int i = 0; i < MAX_LEVEL; i++) {
    sequencia[i] = random(0, 4);
  }
  delay(1000);
}

// Função para mostrar a sequência de LEDs e tocar os tons
// Faz um for que se refere ao nível do jogador.
void mostrarSequencia() {
  for (int i = 0; i < nivel; i++) {
    int led_a_acender = sequencia[i];
    digitalWrite(leds[led_a_acender], HIGH);
    tone(BUZZER, tones[led_a_acender]); // Toca o tom correspondente ao LED
    delay(velocidade);
    digitalWrite(leds[led_a_acender], LOW);
    noTone(BUZZER); // Desliga o buzzer
    delay(200);
  }
  delay(500);
}

// Função para obter a sequência do jogador
// Armazena a informação passada pelo jogador e no final manda para verificação
void obterSequenciaJogador() {
  int indice_jogador = 0;

  while (indice_jogador < nivel) {
    for (int i = 0; i < 4; i++) {
      if (digitalRead(botoes[i]) == LOW) {
        player_sequence[indice_jogador] = i;
        digitalWrite(leds[i], HIGH);
        tone(BUZZER, tones[i]); // Toca o tom correspondente ao botão pressionado
        delay(200);
        digitalWrite(leds[i], LOW);
        noTone(BUZZER); // Desliga o buzzer
        indice_jogador++;
        delay(200);
      }
    }
  }

  verificarSequenciaJogador();
}

// Função para verificar a sequência do jogador
// Verficia de a sequência inserida pelo jogador é a mesma da gerada
void verificarSequenciaJogador() {
  for (int i = 0; i < nivel; i++) {
    if (player_sequence[i] != sequencia[i]) {
      nivel = 0;
      return;
    }
  }
  nivel++;
  delay(500);
}

// Função para reiniciar o jogo
void reiniciarJogo() {
  nivel = 0;
}


// Função de setup que chama a função  "iniciarJogo();"
void setup() {
  configurarPinos();
  pinMode(BOTAORESET, INPUT_PULLUP);
  
  // Espera até que o botão de reset seja pressionado para iniciar o jogo
  while (digitalRead(BOTAORESET) == HIGH) {
    // Piscar LEDs um por um (antes de começar o jogo)
    for (int i = 0; i < 4; i++) {
      digitalWrite(leds[i], HIGH);
      delay(100);
      digitalWrite(leds[i], LOW);
      delay(100);
    }
  }
  iniciarJogo();
}


// Função de loop que ajusta o botão de reset e verifica se o nível do jogador é menor ou igual ao nívle máximo.
void loop() {
  if (nivel == 0) {
    if (digitalRead(BOTAORESET) == LOW) {
      iniciarJogo();
    }
  } else if (nivel <= MAX_LEVEL) {
    mostrarSequencia();
    obterSequenciaJogador();
  } else {
    reiniciarJogo();
  }
}
