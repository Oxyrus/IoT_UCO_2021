#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>


// Replace with your network credentials
const char* ssid = "xxxxx";
const char* password = "xxxxxx";


// Assign output variables to GPIO pins
const int Led1 = D5;
const int Led2 = D6;

// WebServer Instantiation
ESP8266WebServer server(80);
String MyWeb="";

 
void setup(void){

  // creation of web server titles and buttons
  MyWeb +="<meta http-equiv='refresh' content='3'><title>Practice 1- IoT-2021</title>\n";
  MyWeb +="<h1>Practica 1- Control Leds</h1>";
  MyWeb +="<h3>LED 1 <a href=\"Led1Encendido\"><button>ON</button></a>&nbsp;<a href=\"Led1Apagado\"><button>OFF</button></a></h3>\n";
  MyWeb += "<h3>LED 2 <a href=\"Led2Encendido\"><button>ON</button></a>&nbsp;<a href=\"Led2Apagado\"><button>OFF</button></a></h3>\n";
  MyWeb += "<h5>IoT- Jefferson Buritica</h5>";

  // pins configuration
  pinMode(Led1, OUTPUT);
  pinMode(Led2, OUTPUT);

  digitalWrite(Led1, LOW);
  digitalWrite(Led2, LOW);
  

  //Serial Comunnication and Wifi Connection kick off
  Serial.begin(115200);
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
  

  //Start Web Server and notify via serial comm.

  server.begin();
  Serial.println("HTTP server started");

  server.on("/", [](){
    server.send(200, "text/html", MyWeb);
  });

  server.on("/Led1Encendido", [](){
    server.send(200, "text/html", MyWeb);
    digitalWrite(Led1, HIGH);
  });

  server.on("/Led1Apagado", [](){
    server.send(200, "text/html", MyWeb);
    digitalWrite(Led1, LOW);
  });

  server.on("/Led2Encendido", [](){
    server.send(200, "text/html", MyWeb);
    digitalWrite(Led2, HIGH); 
  });

  server.on("/Led2Apagado", [](){
    server.send(200, "text/html", MyWeb);
    digitalWrite(Led2, LOW);
  });
    
 
}

 
void loop(void){
server.handleClient();
 
}
  

