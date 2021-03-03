#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

//Credenciales de la red lo_cal
const char* ssid = "*****";
const char* password = "****";

//Se asignan los pines D6=12 Y D5=14
int PINLEDD5 = 14;
int PINLEDD6 = 12;



// WebServer Instantiation
WiFiServer server(80);

 
void setup(void){
  

  //Serial Comunnication and Wifi Connection kick off
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  //Definimos que los pines son de salida
  pinMode(PINLEDD5,OUTPUT);
  pinMode(PINLEDD6,OUTPUT);
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
  digitalWrite(PINLEDD5, LOW);
  digitalWrite(PINLEDD6, LOW);
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
    digitalWrite(PINLEDD5, HIGH);
  }
  if(peticion.indexOf("LED=OFF") != -1)
  {
    digitalWrite(PINLEDD5, LOW);
  }

  if(peticion.indexOf("LED2=ON") != -1)
  {
    digitalWrite(PINLEDD6, HIGH);
  }
  if(peticion.indexOf("LED2=OFF") != -1)
  {
    digitalWrite(PINLEDD6, LOW);
  }


  client.println("HTTP/1.1 200 OK");
  client.println("");
  client.println("");
  client.println("");
  client.println("");
  //pagina del server
  client.println("<!DOCTYPE html>");
  client.println("<html lang='en'>");
  client.println("<head>");
  client.println("<meta charset='UTF-8'>");
  client.println("<meta name='viewport' content='width=device-width, initial-scale=1.0'>");
  client.println("<title>IoT práctica 1</title>");
  client.println("</head>");
  client.println("<body>");
  client.println("<div> ");
  client.println("<h1>On/Off LED</h1>");
  client.println("<br>");
  client.println("<h2>LED RED</h2>");
  client.println("<button style='background-color:white;border:2px solid red;color:red;'");
  client.println("type='button' onClick=location.href='/LED=OFF'><h2>Apagar</h2>");
  client.println("</button>");
  client.println("<button style='background-color:white;border:2px solid blue;color:blue;'");
  client.println("type='button' onClick=location.href='/LED=ON'><h2>Encender</h2>");
  client.println("</button>"); 
  client.println("<br><br>");
  client.println("<h2>LED BLUE</h2>");
  client.println("<button style='background-color:white;border:2px solid green;color:green;'"); 
  client.println("type='button' onClick=location.href='/LED2=OFF'><h2>Apagar</h2>");
  client.println("</button>");
  client.println("<button style='background-color:white;border:2px solid yellow;color:red;'"); 
  client.println("type='button' onClick=location.href='/LED2=ON'><h2>Encender</h2>");
  client.println("</button>");
  client.println("</div>");
  client.println("</body>");
  client.println("</html>");
  
  delay(10);

}