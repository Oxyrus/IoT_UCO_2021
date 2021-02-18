 #include <ESP8266WiFi.h>
 
const char* ssid = "xxxx";
const char* password = "xxxx";
 
int ledPin1 = 13; // PIN D7
int ledPin2 = 5; // PIN D1
String Respuesta1 = "Led 1 apagado.", Respuesta2 = "Led 2 apagado.";
WiFiServer server(80);
 
void setup() {
  Serial.begin(115200);  
 
  //Declarar puertos de salida.
  pinMode(ledPin1, OUTPUT);  
  digitalWrite(ledPin1, LOW);
  pinMode(ledPin2, OUTPUT);
  digitalWrite(ledPin2,LOW);
 
  // Connect to WiFi network  
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("Connected to: ");
  Serial.println(ssid);

   // Print the IP address  
  Serial.print("IP ADDRESS: ");
  Serial.print(WiFi.localIP());  

  // Start the server
  server.begin(); 
  Serial.println("");
  Serial.println("HTTP server started.");
}
 
void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
 
  // Wait until the client sends some data  
  while(!client.available()){
    delay(1);
  }
 
  // Read the first line of the request
  String request = client.readStringUntil('\r');  
  client.flush();
 
  // Match the request    
  if (request.indexOf("/LED1=ENCENDIDO") != -1)  {    
    digitalWrite(ledPin1, HIGH);    
    Respuesta1 = "Led 1 encendido. ";
  }
  else if (request.indexOf("/LED1=APAGADO") != -1)  {    
    digitalWrite(ledPin1, LOW);    
    Respuesta1 = "Led 1 apagado. ";
  }
  else if (request.indexOf("/LED2=APAGADO") != -1)  {    
    digitalWrite(ledPin2, LOW);    
    Respuesta2 = "Led 2 apagado. ";
  }
  else if (request.indexOf("/LED2=ENCENDIDO") != -1){
    digitalWrite(ledPin2, HIGH);    
    Respuesta2 = "Led 2 encendido. ";
  } 

  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one  
  client.println("<!DOCTYPE HTML>");  
  client.println("<html>");   
  client.println("<body  background=\" https://i.pinimg.com/originals/39/83/8c/39838ca9413e1da738082379179dfeae.jpg\" \">"); 
  client.println("<center>");
  client.println("<br><br>");
  client.println("<br><br>");  
  client.println("Control de luces LED.");        
  client.println("<br><br>");
  client.println("<br><br>");
  client.println("LED 1:");
  client.println("<br><br>");
  client.println("<a href=\"/LED1=ENCENDIDO\"\"><button>ENCENDER </button></a>");
  client.println("<a href=\"/LED1=APAGADO\"\"><button>APAGAR </button></a><br />");    
  client.print(Respuesta1);
  client.println("<br><br>");
  client.println("<br><br>");
  client.println("LED 2:");
  client.println("<br><br>");
  client.println("<a href=\"/LED2=ENCENDIDO\"\"><button>ENCENDER </button></a>");
  client.println("<a href=\"/LED2=APAGADO\"\"><button>APAGAR </button></a><br />");    
  client.print(Respuesta2);
  client.println("</center>");  
  client.println("</body>");
  client.println("</html>");    
}


