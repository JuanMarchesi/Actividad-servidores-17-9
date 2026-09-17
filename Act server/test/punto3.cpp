#include <Arduino.h>

#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "CESJT";
const char* password = "itisjtsmg";

int rojo= 1;
int amarillo= 2;
int verde= 3;

WebServer server(80);

const char pagina_template[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="es">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Semáforo</title>

    <style>
        body {
            background-color: white;
            text-align: center;
            margin: 0;
            font-family: Arial, sans-serif;
        }

        .titulo {
            font-family: Impact, sans-serif;
            font-size: 45px;
            font-weight: bold;
            text-decoration: underline;
        }

        .boton {
            display: block;
            width: 200px;
            height: 200px;
            margin: 15px auto;
            color: black;
            font-size: 23px;
            border: 3px solid black;
            border-radius: 100px;
            cursor: pointer;
        }

        .lento {
            background-color: red;
        }

        .normal {
            background-color: yellow;
        }

        .rápido {
            background-color: green;
        }

        .emergencia {
            background-color: orange;
        }

        #modo {
            display: block;
            margin-top: 20px;
            font-size: 23px;
        }
    </style>
</head>

<body>

    <h1 class="titulo">SEMÁFORO</h1>

    <button class="boton lento" onclick="seleccionarModo('lento')">
        LENTO
    </button>

    <button class="boton normal" onclick="seleccionarModo('normal')">
        NORMAL
    </button>

    <button class="boton rápido" onclick="seleccionarModo('rápido')">
        RÁPIDO
    </button>

    <button class="boton emergencia" onclick="seleccionarModo('emergencia')">
        EMERGENCIA
    </button>

    <span id="modo">Modo: <strong>XXX</strong></span>

    <script>
        function seleccionarModo(modo) {
            document.getElementById("modo").innerHTML =
                "Modo: <strong>" + modo + "</strong>";
        }
    </script>

</body>
</html>
)rawliteral";





void setup() {
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

  server.on("/lento", []() {
    String pagina = pagina_template;

    pagina.replace("Modo", "LENTO");

    digitalWrite(rojo, HIGH);
    digitalWrite(amarillo, LOW);
    digitalWrite(verde, LOW);
    delay(70000);
    digitalWrite(rojo, LOW);
    digitalWrite(amarillo, HIGH);
    digitalWrite(verde, LOW);
    delay(3000);
    digitalWrite(rojo, LOW);
    digitalWrite(amarillo, HIGH);
    digitalWrite(verde, LOW);
    delay(50000);

  });
  server.on("/normal", []() {
    String pagina = pagina_template;

    pagina.replace("Modo", "NORMAL");

    digitalWrite(rojo, HIGH);
    digitalWrite(amarillo, LOW);
    digitalWrite(verde, LOW);
    delay(45000);
    digitalWrite(rojo, LOW);
    digitalWrite(amarillo, HIGH);
    digitalWrite(verde, LOW);
    delay(2000);
    digitalWrite(rojo, LOW);
    digitalWrite(amarillo, HIGH);
    digitalWrite(verde, LOW);
    delay(65000);
  });
  server.on("/rapido", []() {
    String pagina = pagina_template;

    pagina.replace("Modo", "RAPIDO");

    digitalWrite(rojo, HIGH);
    digitalWrite(amarillo, LOW);
    digitalWrite(verde, LOW);
    delay(20000);
    digitalWrite(rojo, LOW);
    digitalWrite(amarillo, HIGH);
    digitalWrite(verde, LOW);
    delay(1000);
    digitalWrite(rojo, LOW);
    digitalWrite(amarillo, HIGH);
    digitalWrite(verde, LOW);
    delay(40000);
  });
  server.on("/emergencia", []() {
    String pagina = pagina_template;

    pagina.replace("Modo", "EMERGENCIA");

    digitalWrite(rojo, LOW);
    digitalWrite(amarillo, LOW);
    digitalWrite(verde, LOW);
    delay(1500);
    digitalWrite(rojo, HIGH);
    digitalWrite(amarillo, HIGH);
    digitalWrite(verde, LOW);
    delay(1500);
    
  });

  server.begin();
}

void loop(){

   server.handleClient();
}