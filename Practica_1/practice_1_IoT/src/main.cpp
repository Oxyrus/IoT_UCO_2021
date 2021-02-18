#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

//Credenciales de la red local
const char* ssid = "DARKSOUL";
const char* password = "Sezugo0712";

//Se asignan los pines D0=16 Y D5=14
int pinLedGPI014 = 14;
int pinLedGPI016 = 16;

//Se les asigna un estado a cada pin, es importante aclarar que es posible manejarlo con LOW-HIGH
int estadoLedGPI014 = 0;
int estadoLedGPIO16 = 0;

// WebServer Instantiation
WiFiServer server(80);

//Web Page Variable
String webPage = "";
 
void setup(void){
  

  //Serial Comunnication and Wifi Connection kick off
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  //Definimos que los pines son de salida
  pinMode(pinLedGPI014,OUTPUT);
  pinMode(pinLedGPI016,OUTPUT);
  Serial.println("");

  // Wait for connection (Intenta conectarse a la red WiFi)
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  //Los datos de la red en la cual estoy conectado y su ip para la conexión con el servidor
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  

  //Start Web Server and notify via serial comm.
  server.begin();
  Serial.println("HTTP server started");
  //Low a los pines
  digitalWrite(pinLedGPI014, 0);
  digitalWrite(pinLedGPI016, 0);
}
 
void loop(void){
  //Se crea un objete de la clase WifiCliente
  // avalaible() detecta un cliente nuevo del objeto de la clase WifiServer
  WiFiClient client = server.available(); 
  
  //Si no hay un cliente detectado vuelve a entrar al Loop
  if(!client){
    return;
  }
  
  Serial.println("Recibiendo una petición... ");
  //espera a un cliente diponible
  while(!client.available()){ 
    delay(1);
  }


  //lee la peticion del cliente
  String peticion = client.readStringUntil('\r'); 
  Serial.println(peticion);
  //limpia la peticion del cliente pero la peticion se mantiene 
  client.flush(); 


  //Validaciones
  if(peticion.indexOf("LED=ON") != -1)
  {
    estadoLedGPI014=1;
  }
  if(peticion.indexOf("LED=OFF") != -1)
  {
    estadoLedGPI014=0;
  }

  if(peticion.indexOf("LED2=ON") != -1)
  {
    estadoLedGPIO16=1;
  }
  if(peticion.indexOf("LED2=OFF") != -1)
  {
    estadoLedGPIO16=0;
  }

  //Se le asigna el estado al pin (Dependiendo de las validaciones) prende o apaga
  digitalWrite(pinLedGPI014, estadoLedGPI014);
  digitalWrite(pinLedGPI016, estadoLedGPIO16);

  client.println("HTTP/1.1 200 OK");
  client.println("");
  client.println("");
  client.println("");
  client.println("");
  //pagina del server
  client.println("<!DOCTYPE html>");
  client.println("<html lang='en'>");
  client.println("  <head>");
  client.println("      <meta charset='UTF-8'>");
  client.println("      <meta name='viewport' content='width=device-width, initial-scale=1.0'>");
  client.println("      <title>Control de LED</title>");
  client.println("  </head>");
  client.println("  <body style='font-family: Century gothic; background-color:rgb(38, 38, 38); width: 2000;'>");
  client.println("      <center>");
  client.println("      <div> ");
  client.println("          <h1 style='color:rgb(251, 251, 251);'>IoT-Practice I</h1>");
  client.println("      <hr style='border-color:rgb(251, 251, 251);'>");
  client.println("      <br>");
  client.println("      <h2 style='color:rgb(251, 251, 251);'>LED 1</h2>");
  client.println("          <h4 style='color:rgb(251, 251, 251);'>Select Option</h4>");
  client.println("          <button style='background-color:rgb(249, 49, 84);  color:rgb(251, 251, 251); border-radius: 10px; border-color: rgb(249, 49, 84);' ");
  client.println("              type='button' onClick=location.href='/LED=OFF'><h2>OFF</h2>");
  client.println("          </button>");
  client.println("          <button style='background-color:rgb(0, 183, 74); color:rgb(251, 251, 251); border-radius: 10px; border-color: rgb(0, 183, 74);'");
  client.println("              type='button' onClick=location.href='/LED=ON'><h2>ON</h2>");
  client.println("          </button>"); 
  client.println("      <br><br>");
  client.println("      <h2 style='color:rgb(251, 251, 251);'>LED 2</h2>");
  client.println("          <h4 style='color:rgb(251, 251, 251);'>Select Option</h4>");
  client.println("          <button style='background-color:rgb(249, 49, 84);  color:rgb(251, 251, 251); border-radius: 10px; border-color: rgb(249, 49, 84);'"); 
  client.println("              type='button' onClick=location.href='/LED2=OFF'><h2>OFF</h2>");
  client.println("          </button>");
  client.println("          <button style='background-color:rgb(0, 183, 74); color:rgb(251, 251, 251); border-radius: 10px; border-color: rgb(0, 183, 74);'"); 
  client.println("              type='button' onClick=location.href='/LED2=ON'><h2>ON</h2>");
  client.println("          </button>");
  client.println("      <br>");   
  client.println("      </div>");
  client.println("  </center>");
  client.println("  </body>");
  client.println("</html>");
  
  delay(10);
  Serial.println("Petición del cliente finalizada");
  Serial.println(""); 

}