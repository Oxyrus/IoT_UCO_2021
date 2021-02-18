#include <Arduino.h>
#include <ESP8266WiFi.h>

//Definicion De los Pines De Las Cargas
#define LED1 D2
#define LED2 D1

//Informacion De La Red
const char *Nombre = "";//¿porque hay que poner "*"?
const char *Password="";

//Asignacion de Ip estatica
//IPAddress ip(192,160,0,10);
//IPAddress gateway(192,160,0,1);
//IPAddress subnet(255,255,255,0);

//Puerto 80 TCP: Es Para La Navegacion Web HTTP
WiFiServer server(80);

void setup() {
  //Configuracion Comunicacio Serial
  Serial.begin(115200);
  delay(10);

  //Configuracion De Los Pines
  pinMode(LED1, OUTPUT);
  pinMode(LED2,OUTPUT);
  digitalWrite(LED1,LOW);
  digitalWrite(LED2,LOW);

  //conexion al wifi
  Serial.println("Conectandose a :");
  Serial.println(Nombre);
  /*Hay Tres Modos De Conectar El NodeMcu:
  # Modo STA o Estacion: Conexion Del NodeMcu Al Router
  # Modo Ap : Conexion Del NodeMcu Con Otros Dispositivos
  Para Indicarles La Red A La Que Deben Coctarse Para La Comunicacion 
  # Modo De Combinacion De Ambas   */
  WiFi.mode(WIFI_STA);//Modo Estacion

  //Como La Conexion Es Estatica, Configuramos Los Parametros
  //WiFi.config(ip,gateway,subnet);
  WiFi.begin(Nombre,Password);

  //Imprimir Puntos Mientras Carga La Conexion
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print("*");
    delay(500);
  }
  Serial.println("Conectado A La Red");
  //***************************Inicio Del Servidor*************************************
  server.begin();
  Serial.println("Servidor Iniciado");

  //Impremir La Direccion IP del Servidor 
  Serial.print("URL Para Comunicarse Con El NodeMcu: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.print("/");
}

void loop() {
  
  //Serial.println(WiFi.localIP());
  
  //El Servido Va  Esperar Que Haya Un Cliente
  WiFiClient Client = server.available();
  if (!Client)
  {
    return;
  }
  Serial.print("Nuevo Cliente");
  //Esperando Que El Cliente Mande Una Solicitud
  while (!Client.available())
  {
    delay(1);
  }
  //Se Guarda En Una Variable La Solicitud Del Cliente
  String Request= Client.readStringUntil('\r');
  Serial.println(Request); //Se Imprime La Solicitud
  Client.flush();//Borrar Datos Cliente
  
  //Con El IndexOf, Se Busca En El String Guardado "Request"
  // Si Se Encuentra Una Palabra Como "/LED=OFF".etc
  if(Request.indexOf("/LED=OFF1")!=-1){
    digitalWrite(LED1,LOW);
  }
  if(Request.indexOf("/LED=ON1")!=-1){
    digitalWrite(LED1,HIGH);
  }
  if(Request.indexOf("/LED=BLINK1")!=-1){
    for (int i = 0; i < 10; i++)
    {
     digitalWrite(LED1,HIGH);
     delay(200);
     digitalWrite(LED1,LOW);
     delay(200);
    }
  }

  if(Request.indexOf("/LED=OFF2")!=-1){
    digitalWrite(LED2,LOW);
  }
  if(Request.indexOf("/LED=ON2")!=-1){
    digitalWrite(LED2,HIGH);
  }
  if(Request.indexOf("/LED=BLINK2")!=-1){
    for (int i = 0; i < 10; i++)
    {
     digitalWrite(LED2,HIGH);
     delay(200);
     digitalWrite(LED2,LOW);
     delay(200);
    }
  }

   //***********************Respuesta Del Servidor*************************
   Client.println("HTTP/1.1 200 OK");
   Client.println("Content-Type: Text/html");
   Client.println("<!DOCTYPE html>\n");
   Client.println("<html lang=\"en\">\n");
   Client.println("<head>\n");
   Client.println("    <meta charset=\"UTF-8\">\n");
   Client.println("    <meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\">\n");
   Client.println("    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n");
   Client.println("    <title>Servidor Web Esp8266</title>\n");
   Client.println("</head>\n");
   Client.println("<body background=\"https://image.freepik.com/vector-gratis/fondo-iot-elementos-dibujados-mano_23-2147632292.jpg\"> \n");
   Client.println("<h1 style=\"text-align: center;\">Servidor Web Esp8266</h1>\n");
   Client.println("<p style=\"justify-content: space-evenly;\">\n");
   Client.println("<p style=\"text-align: center;\">\n");
   Client.println("    <button onclick=location.href=\"LED=ON1\" style=\"font-size: 20px; color: red; background: black;\">Encender Led1</button>\n");
   Client.println("    <button onclick=location.href=\"LED=OFF1\" style=\"font-size: 20px; color: red; background: black;\">Apagar Led1</button>\n");
   Client.println("    <button onclick=location.href=\"LED=BLINK1\" style=\"font-size: 20px; color: red; background: black;\">Parpadear Led1</button>\n");
   Client.println("<br><br><br>\n");
   Client.println("    <button onclick=location.href=\"LED=ON2\" style=\"font-size: 20px; color: red; background: black;\">Encender Led2</button>\n");
   Client.println("    <button onclick=location.href=\"LED=OFF2\" style=\"font-size: 20px; color: red; background: black;\">Apagar Led2</button>\n");
   Client.println("    <button onclick=location.href=\"LED=BLINK2\" style=\"font-size: 20px; color: red; background: black;\">Parpadear Led2</button>");
   Client.println("</p>\n");
   Client.println("</p>\n");
   Client.println("</body>\n");
   Client.println("</html>");
   
   delay(1);
   Serial.println("Cliente desconectado");
   Serial.println("");

  
}