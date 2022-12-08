/*
 WiFi Web Server LED Blink

 A simple web server that lets you blink an LED via the web.
 This sketch will print the IP address of your WiFi Shield (once connected)
 to the Serial monitor. From there, you can open that address in a web browser
 to turn on and off the LED on pin 5.

 If the IP address of your shield is yourAddress:
 http://yourAddress/H turns the LED on
 http://yourAddress/L turns it off

 This example is written for a network using WPA2 encryption. For insecure
 WEP or WPA, change the Wifi.begin() call and use Wifi.setMinSecurity() accordingly.

 Circuit:
 * WiFi shield attached
 * LED attached to pin 5

 created for arduino 25 Nov 2012
 by Tom Igoe

ported for sparkfun esp32 
31.01.2017 by Jan Hendrik Berlin
 
 */

#include <WiFi.h>

const char* ssid = "Inteli-COLLEGE";
const char* password = "QazWsx@123";

WiFiServer server(80);

#define RIGHT_LED_PIN 4

void setup() {
  Serial.begin(115200);
  
  pinMode(RIGHT_LED_PIN, OUTPUT);      // LED Azul (direito)

  delay(10);

  // We start by connecting to a WiFi network

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  server.begin();
}

int value = 0;

void loop() {
  WiFiClient client = server.available();  // listen for incoming clients

  if (client) {                     // if you get a client,
    Serial.println("New Client.");  // print a message out the serial port
    String currentLine = "";        // make a String to hold incoming data from the client
    while (client.connected()) {    // loop while the client's connected
      if (client.available()) {     // if there's bytes to read from the client,
        char c = client.read();     // read a byte, then
        Serial.write(c);            // print it out the serial monitor
        if (c == '\n') {            // if the byte is a newline character

          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:


          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("<body><IMG SRC='https://www.how-to-draw-funny-cartoons.com/images/cartoon-background-001.png' style='position: absolute; left: 0px; top: 0px; width: 1540px; height: 735px;'><INPUT TYPE='button' VALUE='1' onClick='jogar(1)' style='width: 15%; height: 15%; font-size: 30px; font-weight: bold; position: absolute; left: 20%; bottom: 80%;'><INPUT TYPE='button' VALUE='2' onClick='jogar(2)' style='width: 15%; height: 15%; font-size: 30px; font-weight: bold; position: absolute; right: 20%; bottom: 80%;'><SPAN ID='vencedor' style='position: absolute; left: 44%; top: 30%; font-size: 60px; font-weight: bold;'></SPAN><SPAN ID='tempo' style='position: absolute; left: 50%; bottom: 80%; font-size: 60px; font-weight: bold;'>20</SPAN><SPAN ID='cont1' style='position: absolute; left: 10%; bottom: 86%; font-size: 30px; font-weight: bold;'>0</SPAN><SPAN ID='cont2' style='position: absolute; right: 10%; bottom: 86%; font-size: 30px; font-weight: bold;'>0</SPAN><IMG ID='corda' SRC='https://cdn-icons-png.flaticon.com/512/497/497132.png' style='position: absolute; left: 500px; top: 35%;'></body><script>var tempo = 20;var cronometro = setInterval(function() {tempo = tempo - 1;document.getElementById('tempo').innerHTML = tempo;if (tempo <= 0) {clearInterval(cronometro);document.getElementById('tempo').innerHTML = 'Fim!';}}, 1000);var cont1 = 0;var cont2 = 0;function jogar(botao) {if (tempo > 0) {if (botao == 1) {cont1 = cont1 + 1;document.getElementById('cont1').innerHTML = cont1;} else {cont2 = cont2 + 1;document.getElementById('cont2').innerHTML = cont2;}var corda = document.getElementById('corda');if (botao == 1) {corda.style.left = parseInt(corda.style.left) - 25 + 'px';}if (botao == 2) {corda.style.left = parseInt(corda.style.left) + 25 + 'px';}}var vencedor = document.getElementById('vencedor');if (cont1> cont2) {document.getElementById('vencedor').innerHTML = 'Jogador 1';if (parseInt(corda.style.left)<=0) {document.getElementById('vencedor').innerHTML = 'Jogador 1';tempo = 0;}} else if (cont1 < cont2) {document.getElementById('vencedor').innerHTML = 'Jogador 2';if (parseInt(corda.style.left)>=1000) {document.getElementById('vencedor').innerHTML = 'Jogador 2';tempo = 0;}} else {document.getElementById('vencedor').innerHTML = 'Empate';}}</script></body>");
            
            // The HTTP response ends with another blank line:
            client.println();
            // break out of the while loop:
            break;
          } else {  // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }            
      }
    }
    // close the connection:
    client.stop();
    Serial.println("Client Disconnected.");
  }
}
