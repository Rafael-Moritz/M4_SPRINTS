#include <vector>
const int led1 = 9;  //branco
const int led2 = 10;  //azul
const int led3 = 11;   // amarelo
const int led4 = 12;   // verde
const int buzzer = 1;
const int botao1 = 5;  // laranja salva
const int botao2 = 4;   // amarelo toca
int combinacao[] = {};
int tocando = 0;
int c[50] = {};
int count = 0;

void setup() {
  Serial.begin(115200);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(botao1, INPUT_PULLUP);
  pinMode(botao2, INPUT_PULLUP);
}
int transformar() {
  int analogValue = analogRead(2);
  int luminosidade = map(analogValue, 32, 4063, 15, 0);
  Serial.println(luminosidade);
  return luminosidade;
}
void armazenar(int luminosidade) {
  if (count < 50) {
    c[count] = luminosidade;
    play(luminosidade);
    count++;
  }
}
void play(int luminosidade) {
  int freq = luminosidade * 100;
  if (luminosidade % 2 == 1) {
    digitalWrite(led1, HIGH);
    tone(buzzer, freq);
  } else if (luminosidade % 2 == 0) {
    digitalWrite(led1, LOW);
    tone(buzzer, freq);
  }
  if (luminosidade / 2 % 2 == 1) {
    digitalWrite(led2, HIGH);
    tone(buzzer, freq);
  } else if (luminosidade / 2 % 2 == 0) {
    digitalWrite(led2, LOW);
    tone(buzzer, freq);
  }
  if (luminosidade / 2 / 2 % 2 == 1) {
    digitalWrite(led3, HIGH);
    tone(buzzer, freq);
  } else if (luminosidade / 2 / 2 % 2 == 0) {
    digitalWrite(led3, LOW);
    tone(buzzer, freq);
  }
  if (luminosidade > 7) {
    digitalWrite(led4, HIGH);
    tone(buzzer, freq);
  }
  else if (luminosidade <= 7) {
    digitalWrite(led4, LOW);
    tone(buzzer, freq);
  }
  delay(1000);
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  digitalWrite(led4, LOW);
  noTone(buzzer);
}
void executar() {
  for (int i = 0; i < count; i++) {
    play(c[i]);
  }
  count = 0;
  c[50] = {};
}
void loop() {
  if (digitalRead(botao1) == LOW) {
    int luminosidade = transformar();
    armazenar(luminosidade);
  }
  if (digitalRead(botao2) == LOW) {
    executar();
  }
}