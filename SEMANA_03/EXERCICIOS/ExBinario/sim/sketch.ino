
int j = 0;
int k = 0;
int sensorLDR;
int notas[100] = {};

void setup() {
  // put your setup code here, to run once:
  
  Serial.begin(115200);
  pinMode(2, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(14, OUTPUT);
  pinMode(27, OUTPUT);
  pinMode(26, OUTPUT);
  pinMode(23, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
}

void loop() {

int analogValue = analogRead(2);
// Serial.println(analogValue, DEC); 
int luminosidade = map (analogValue, 64, 8126, 15, 0);
Serial.println(luminosidade);

int res = 0;

for (int i = 0; i <= luminosidade; i++){
  delay(4000);
  int freq = i*100;
  int l1 = (i);
  int l2 = (i);
  int l3 = (i);
  int l4 = (i);
  delay(1000);

  
  if(i == luminosidade+1){

  }
  else{
    if (i != luminosidade){
    delay(1000);
    }
    if (l1%2 == 1) {digitalWrite(27, HIGH); //branco 
      tone(26, freq, 1000);}
    else if (l1%2 == 0) {digitalWrite(27, LOW);
      tone(26, freq, 1000);}
    if (l2/2%2 == 1) {digitalWrite(14, HIGH); //amarelo 
      tone(26, freq, 1000);}
    else if (l2/2%2 == 0) {digitalWrite(14, LOW);
      tone(26, freq, 1000);}
    if (l3/2/2%2 == 1) {digitalWrite(12, HIGH); //azul 
      tone(26, freq, 1000);}
    else if (l3/2/2%2 == 0) {digitalWrite(12, LOW);
      tone(26, freq, 1000);}
    if (l4 > 7) {digitalWrite(13, HIGH); //vermelho 
      tone(26, freq, 1000);}
    else if (l4 <= 7) {digitalWrite(13, LOW);
      tone(26, freq, 1000);}

    int botao1 = digitalRead(23);

    if (botao1 == 1) {
      Serial.println("faz nada");
    }
    else if (botao1 == 0) {
      Serial.print("guarda a nota ");
      Serial.println(i);
 
      notas[j] = i;
      j++;
      botao1 = 1;
      for (k = 0; k <= j; k++){
      Serial.println(notas[k]);
      }
      }
    int botao2 = digitalRead(5);

  if (botao2 == 0) {
      Serial.println("toca as notas");
      for (k = 0; k <= j; k++){
      tone(26, notas[k], 1000);} 
    }
    }
  }
}