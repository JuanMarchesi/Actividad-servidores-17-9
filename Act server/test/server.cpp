#include <Arduino.h>

#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "CESJT";
const char* password = "itisjtsmg";

const int ledPin = 2; 

WebServer server(80);

bool ledEncendido = true;

// pagina
const char pagina_template[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <meta charset='utf-8'>
  <title>Servidor Web ESP32</title>
  <style>
    body { background-color: black; text-align: center; }
    .titulo { font-family: 'Courier', monospace; font-weight: bold; font-style: italic; font-size: 32px; color: white; }
    .boton { width: 80px; height: 45px; background-color: yellow; color: black; border: 2px solid black; border-radius: 80px; font-size: 14px; font-weight: bold; cursor: pointer; }
  </style>
</head>
<body>
  <h1 class='titulo'>BLINK DE LED INTERNO</h1>
  <p><a href='/toggle'><button class='boton'>__BOTON_TEXTO__</button></a></p>
</body>
</html>
)rawliteral";


void toggle(){
  digitalWrite(ledPin,ledEncendido);
    ledEncendido = !ledEncendido;
    server.sendHeader("Location", "/"); // dice que la página se vaya a /
    server.send(302, "text/plain", ""); // 302 dice que el /toggle no está y que vaya a la locación de antes
}

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);

  // conexion al wifi como antes
  Serial.print("Conectando a ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  int timeout = 20; // 20 intentos de 500ms = 10 segundos
  while (WiFi.status() != WL_CONNECTED && timeout > 0) {
    delay(500);
    Serial.print(".");
    timeout--;
  }

  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("\nFallo la conexion. Reiniciando...");
    delay(1000);
    ESP.restart();
  }
  Serial.println("\nWiFi conectado!");
  Serial.print("Dirección IP: http://");
  Serial.println(WiFi.localIP());

  server.on("/", []() {
    
    String pagina = pagina_template; //hago una variable para no modificar a la original
    //parte para cambiar lo que dice el boton una vez que se prende o apaga
    String textoBoton;
    if (ledEncendido == true)  textoBoton = "ON";
    else textoBoton = "OFF";
    
    //pagina.replace busca el texto y lo reemplaza con lo que pongas. 
    pagina.replace("__BOTON_TEXTO__", textoBoton);

    server.send(200, "text/html", pagina);
  });

  server.on("/toggle",toggle);

  /* OTRA FORMA 
  server.on("/toggle", []() {
    digitalWrite(ledPin,ledEncendido);
    ledEncendido = !ledEncendido;
    server.sendHeader("Location", "/");
    server.send(302, "text/plain", ""); // 302 y send Header para que no me quede en /header
  });*/
  server.begin();
}

void loop() {
  server.handleClient();

  
}