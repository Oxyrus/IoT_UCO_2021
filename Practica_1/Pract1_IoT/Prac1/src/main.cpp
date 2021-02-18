#include <ESP8266WiFi.h>
// #include <WiFiClient.h>
// #include <ESP8266WebServer.h>

const char* ssid = "*****";
const char* password = "******";
const int LED1=5, LED2=13;
bool stat1=false, stat2=false;
 
// WebServer Instantiation
WiFiServer server(80);

//Web Page Variable
String webPage = "";
 
void setup(void){

  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  
  //HTML page
  webPage += "<html lang='en'><head><meta charset='UTF-8'><meta name='viewport' content='width=device-width, initial-scale=1.0'>";
	webPage += "<title>LEDS</title></head><body><div class='container center-h center-v'><div class='child'><h1>LED 1</h1>";
	webPage += "<button type='button' onClick=location.href='/ON1'>Encender</button><button type='button' onClick=location.href='/OFF1'>Apagar</button>";
  webPage += "</div></div><div class='container center-h center-v'><div class='child'><h1>LED 2</h1>";
	webPage += "<button type='button' onClick=location.href='/ON2'>Encender</button><button type='button' onClick=location.href='/OFF2'>Apagar</button>";
  webPage += "</div></div></body></html>";

  webPage += "<style>.container { background: #ff0000; margin: 0 0 1rem; height: 10rem; display: flex; align-items: center; }";
  webPage += ".center-h { justify-content: center; width: 13em; }";
  webPage += ".center-v { align-items: center; }";
  webPage += ".child { background: #ffd500; padding: .2rem; }</style>";
  delay(1000);

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
  digitalWrite(LED_BUILTIN, LOW);
}
 
void loop(void){

  WiFiClient user = server.available();
  if (!user)
  {
    return;
  }
  while (user.available())
  {
    delay(1);
  }
  // Serial.println("New user");
  String solic = user.readStringUntil('\r');
  user.flush();

  if (solic.indexOf("/ON1") != -1)
  {
    digitalWrite(LED1, HIGH);
  }
  if (solic.indexOf("/ON2") != -1)
  {
    digitalWrite(LED2, HIGH);
  }
  if (solic.indexOf("/OFF1") != -1)
  {
    digitalWrite(LED1, LOW);
  }
  if (solic.indexOf("/OFF2") != -1)
  {
    digitalWrite(LED2, LOW);
  } 

  user.println(webPage);
}