#include <Arduino.h>

#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "CESJT";
const char* password = "itisjtsmg";

String estado_puls = "XXX";
String color;   

int pulsador1;
int pulsador2;
int pulsador3;

const char pagina_template[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="es">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">

    <title>MONITOR</title>

    <style>

        body {
            background-color: #f0f0f0;
            text-align: center;
        }

        h1 {
            font-family: 'monospace', Tahoma, Geneva, Verdana, sans-serif;
            color: #2c3e50;
        }
        ul{
            list-style-type: none;
            padding : 0;
        }

         .linea_de_estado {
      width: 300px;
      margin: 10px;
      padding: 15px;
      border: 2px solid black
    }
        .suelto{
            background-color: #e74c3c;
        }

        .presionado{
            background-color: green;
        }

    </style>
    <head>
        <body>

            <span>
                <h1>MONITOR DE ENTRADAS DIGITALES 
            </span>
            
            <div class="linea_de_estado">
                __PULADOR_ESTADO__%
            </div>

            <div class="linea_de_estado">
                __PULADOR_ESTADO__%
            </div>

            <div class="linea_de_estado">
                __PULADOR_ESTADO__%
            </div>
        </body>
    </head>


)rawliteral";

void setup(){
     Serial.begin(115200);

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
 }

    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
        String pagina = pagina_template;
        pagina.replace("__PULADOR_ESTADO__", estado_puls);
        pagina.replace(" #d0cfca", color);
        request->send(200, "text/html", pagina);
    }

    void loop(){
        if(pulsador1 = 1){
            color = "#39cb39";
            estado_puls = "presionado"
        }
        else{
            color = "#cc2020";
            estado_puls = "suelto"
        }

    if(pulsador1 = 1){
            color = "#39cb39";
            estado_puls = "presionado"
        }
        else{
            color = "#cc2020";
            estado_puls = "suelto"
        }
    if(pulsador3 = 1){
            color = "#39cb39";
            estado_puls = "presionado"
        }
        else{
            color = "#cc2020";
            estado_puls = "suelto"
        }
