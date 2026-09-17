#include <Arduino.h>

#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "CESJT";
const char* password = "itisjtsmg";

int led [5]  = {0,1,2,3,4}; 

int animacion1 [3][5] {
    {1,1,0,1,0},
    {1,0,1,1,1},
    {1,0,1,1,0}
};

int animacion2 [3][5] {
    {1,1,0,1,0},
    {1,0,1,1,1},
    {0,1,0,0,1}
};

int apagar [5] = {0,0,0,0,0};

WebServer server(80);

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
  <h1 class='titulo'>ANIMACION 1 DE LOS LEDS</h1>
  <p><a href='/anim1'><button class='boton1'>An1</button></a></p>
  <h1 class='titulo'>ANIMACION 2 DE LOS LEDS</h1>
  <p><a href='/anim2'><button class='boton2'>An2</button></a></p>
  <h1 class='titulo'>APAGADO DE LOS LEDS</h1>
  <p><a href='/apagar'><button class='boton3'>Apagar

  </button></a></p>
</body>
</html>
)rawliteral";


void anim1(){

  for (int i = 0; i < 5; i++){
    for (int j = 0; j < 2; j++){
      digitalWrite(led[i], animacion1[j] [i]);
    } 
  }
}

void anim2(){

  for (int i = 0; i < 5; i++){
    for (int j = 0; j < 2; j++){
      digitalWrite(led[i], animacion2[j] [i]);
    } 
  }
}

void apagado(){

  for (int i = 0; i < 5; i++){
      digitalWrite(led[i], apagar[i]);
    } 
  }


void setup() {
  Serial.begin(115200);

  for (int i = 0; i <= 4; i++){

    pinMode(led[i], OUTPUT);

    }

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


    server.send(200, "text/html", pagina);
  });

  server.on("/anim1",[]{
    for (int i = 0; i < 4; i++){
      for (int j = 0; i < 2; j++){
        digitalWrite(led[i], animacion1[j] [i]);
            server.sendHeader("Location", "/");
    server.send(302, "text/plain", ""); // 302 y send Header para que no me quede en /header
    } 
  }  
  });

    server.on("/anim2",[]{

     for (int i = 0; i < 4; i++){
      for (int j = 0; i < 2; j++){
        digitalWrite(led[i], animacion2[j] [i]);
            server.sendHeader("Location", "/");
    server.send(302, "text/plain", ""); // 302 y send Header para que no me quede en /header
    }
  }
  });


  server.on("/apagado",[]{

     for (int i = 0; i < 4; i++)
    {
        digitalWrite(led[i], apagar [i]);
            server.sendHeader("Location", "/");
    server.send(302, "text/plain", ""); // 302 y send Header para que no me quede en /header
    }
  });

  server.begin();

}

void loop(){

   server.handleClient();
}