#include <DHT.h>
#define DHTPIN A1 // pino que estamos conectado
#define DHTTYPE DHT11 // DHT 11
DHT dht(DHTPIN, DHTTYPE);


#include <SPI.h>
// Biblioteca utilizada para comunicação com o Arduino
#include <Ethernet.h>  
 
// A linha abaixo permite definir o endereço físico (MAC ADDRESS) da... 
//placa de rede. 
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

byte ip[] = { 192, 168, 0, 110 };  //Define o endereço IP.
    
// Porta onde estará aberta para comunicação Internet e Arduino.
EthernetServer server(80);  
 
String readString;
int Pin = 7;  //  Pino digital onde será ligado e desligado o LED.
 
void setup(){
 
pinMode(Pin, OUTPUT);  // Define o Pino 9 como saída.
Ethernet.begin(mac, ip);  // Chama o MAC e o endereço IP da placa Ethernet.
server.begin();  //  Inicia o servidor que esta inserido junto a placa Ethernet.
}
 
void loop(){

  int h = dht.readHumidity();
int t = dht.readTemperature();


  EthernetClient client = server.available();
  if (client) {
    while (client.connected()) {
      if (client.available()) {
char c = client.read();
 
        if (readString.length() < 100) {
          readString += c;             
        }

        if (c == '\n') {
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println();
    
// A partir daqui começa os códigos html.
    
client.println("<HTML>");
client.println("<BODY>");
client.println("<H1>Acender/Apagar L&acirc;mpada</H1>"); 
client.println("<H1>Etec - Ara&ccedil;atuba</H1>");
client.println("<hr />");
client.println("<br />");
          
client.println
("<a href=\"/facacomarduino/LampadaOn\"\"><b><h3><center><font color='blue' size='5'>Acender a Lampada</h3> </b></a><br>"); 
client.println
("<a href=\"/facacomarduino/LampadaOff\"\"><b><h3><center><font color='read' size='5'>Apagar a Lampada </h3></a><br />");


   
           
         
          
          //LEITURA DE TEMPERATURA E UMIDADE
          
          client.println("</BODY>");
          client.println("</HTML>");
          
          delay(1);
          client.stop();
          
          if(readString.indexOf("facacomarduino/LampadaOn") > 0)
          {
            digitalWrite(Pin, LOW);  // Liga Lampada.
          }
else {
            if(readString.indexOf("facacomarduino/LampadaOff") > 0)
            {
              digitalWrite(Pin, HIGH);  // Desliga Lampada.
            }
          }
          readString="";    
        }
      }
    }
  }
}
