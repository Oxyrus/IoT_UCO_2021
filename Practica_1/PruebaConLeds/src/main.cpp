
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

// Replace with your network credentials
const char* ssid = "******";
const char* password = "*****";
boolean variar = false;

// WebServer Instantiation
ESP8266WebServer server(80);

//Web Page Variable
String webPage = "";

void handleRoot() {
 server.send(200, "text/html", webPage); 
}

void handleLEDonBlue() { 
  variar = false; 
  digitalWrite(2,HIGH); 
  server.send(200, "text/html", webPage);
}
void handleLEDoffBlue() { 
  variar = false; 
  digitalWrite(2,LOW); 
  server.send(200, "text/html", webPage); 
}
void handleLEDonGreen() { 
  variar = false; 
  digitalWrite(5,HIGH); 
  server.send(200, "text/html", webPage); 
}
void handleLEDoffGreen() {
  variar = false;  
  digitalWrite(5,LOW); 
  server.send(200, "text/html", webPage);
}

void handleLEDVariaron() { 
  variar = true; 
  server.send(200, "text/html", webPage);
}
void handleLEDVariaroff() { 
  variar = false; 
  server.send(200, "text/html", webPage);
}

 
void setup(void){

  pinMode(2,OUTPUT); 
  digitalWrite(2,LOW);
  pinMode(5,OUTPUT); 
  digitalWrite(5,LOW);
  
  //Build Basic Web Page using HTML
  webPage += "<h1>Seleccione el led que desea encender</h1>";
  webPage += "<a><h1>Led azul: </h1></a>";
  webPage += "<a href=\"/LEDAZUL=ON\"\"><button>ON</button></a>";
  webPage += "<a href=\"/LEDAZUL=OFF\"\"><button>OFF</button></a>";
  webPage += "<a><h1>Led verde: </h1></a>";
  webPage += "<a  href=\"/LEDVERDE=ON\"\"><button>ON</button></a>";
  webPage += "<a href=\"/LEDVERDE=OFF\"\"><button>OFF</button></a>";
  webPage += "<a><h1>Variar: </h1></a>";
  webPage += "<a href=\"/VARIAR=ON\"\"><button>ON</button></a>";
  webPage += "<a href=\"/VARIAR=OFF\"\"><button>OFF</button></a>";
  delay(1000);

  //Serial Comunnication and Wifi Connection kick off
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  
  //Web Page handler on root "/" using .send() method from ESP8266WebServer class
  server.on("/", handleRoot);

  server.on("/LEDAZUL=ON", handleLEDonBlue);
  server.on("/LEDAZUL=OFF", handleLEDoffBlue);
  server.on("/LEDVERDE=ON", handleLEDonGreen);
  server.on("/LEDVERDE=OFF", handleLEDoffGreen);
  server.on("/VARIAR=ON", handleLEDVariaron);
  server.on("/VARIAR=OFF", handleLEDVariaroff);
  //Start Web Server and notify via serial comm.
  server.begin();
  Serial.println("HTTP server started");

}
 
void loop(void){
  //Handle client requests to web Server using .handleClient() method from ESP8266WebServer class
  server.handleClient();
  if(variar == true){
    digitalWrite(5,HIGH);
    delay(100);
    digitalWrite(5,LOW);
    digitalWrite(2,HIGH);
    delay(100);
    digitalWrite(2,LOW);
  }
}