#include <Arduino.h>

#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "CESJT";
const char* password = "itisjtsmg";

int pines_7seg1 [7] = {33, 32, 27, 26, 25, 14, 12};
int pines_7seg2 [7] = {2, 15, 18, 19, 21, 22, 23};
int dis7seg [9][7] = {
    (1,1,1,1,1,1,0), //0
    (0,1,1,0,0,0,0), //1
    (1,1,0,1,1,0,1), //2
    (1,1,1,1,0,0,1), //3
    (1,1,1,0,0,1,1), //4
    (1,0,1,1,0,1,1), //5
    (1,0,1,1,1,1,1), //6
    (1,1,1,0,0,0,0), //7
    (1,1,1,1,1,1,1), //8
    (1,1,1,1,0,1,1)  //9
};

bool num = 0;
bool dis_utl = 0;

WebServer server(80);

// pagina
const char pagina_template[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="es">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Pad Numérico</title>

    <style>
        body {
            background-color: #222;
            display: flex;
            justify-content: center;
            align-items: center;
            height: 100vh;
            margin: 0;
            font-family: Arial, sans-serif;
        }

        .contenedor {
            display: flex;
            flex-direction: column;
            align-items: center;
            gap: 20px;
        }

        .superiores {
            display: flex;
            gap: 10px;
        }

        .superiores button {
            width: 125px;
            height: 60px;
            font-size: 25px;
            font-weight: bold;
            border: none;
            border-radius: 10px;
            background-color: #555;
            color: white;
            cursor: pointer;
        }

        .pad {
            display: grid;
            grid-template-columns: repeat(3, 80px);
            gap: 10px;
        }

        .pad button {
            width: 80px;
            height: 80px;
            font-size: 30px;
            font-weight: bold;
            border: none;
            border-radius: 10px;
            background-color: #444;
            color: white;
            cursor: pointer;
        }

        button:hover {
            background-color: #666;
        }

        button:active {
            background-color: #888;
            transform: scale(0.95);
        }
    </style>
</head>

<body>

    <div class="contenedor">

        <div class="superiores">
             <p><a href='/toggle'><button class='boton'>Display 2</button></a></p>
        </div>

        <div class="pad">
            <button onclick="presionar(1)">1</button>
            <button onclick="presionar(2)">2</button>
            <button onclick="presionar(3)">3</button>

            <button onclick="presionar(4)">4</button>
            <button onclick="presionar(5)">5</button>
            <button onclick="presionar(6)">6</button>

            <button onclick="presionar(7)">7</button>
            <button onclick="presionar(8)">8</button>
            <button onclick="presionar(9)">9</button>
        </div>

    </div>

    <script>
        function presionar(numero) {
            console.log("Se presionó el botón: " + numero);
        }
    </script>

</body>
</html>
)rawliteral";


void setup() {
  Serial.begin(115200);

  for (int i = 0; i <= 9; i++){

    pinMode(pines_7seg1 [i], OUTPUT);

    pinMode(pines_7seg2 [i], OUTPUT);
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

  server.begin();


    server.on("/diplay1",[]{
    
        dis_utl=2;
            server.sendHeader("Location", "/");
    server.send(302, "text/plain", ""); // 302 y send Header para que no me quede en /header 
  });

    server.on("/diplay2",[]{
    
        dis_utl=1;
            server.sendHeader("Location", "/");
    server.send(302, "text/plain", ""); // 302 y send Header para que no me quede en /header 
  });

  server.on("/0",[]{
    for (int i = 0; i <= 7; i++)
    {
        digitalWrite(dis7seg [0][i], HIGH);
    }
            server.sendHeader("Location", "/");
    server.send(302, "text/plain", ""); // 302 y send Header para que no me quede en /header 
  });

  server.on("/1",[]{
    for (int i = 0; i <= 7; i++)
    {
        digitalWrite(dis7seg [1][i], HIGH);
    }
            server.sendHeader("Location", "/");
    server.send(302, "text/plain", ""); // 302 y send Header para que no me quede en /header 
  });

    server.on("/2",[]{
    for (int i = 0; i <= 7; i++)
    {
        digitalWrite(dis7seg [2][i], HIGH);
    }
            server.sendHeader("Location", "/");
    server.send(302, "text/plain", ""); // 302 y send Header para que no me quede en /header 
  });

    server.on("/3",[]{
    for (int i = 0; i <= 7; i++)
    {
        digitalWrite(dis7seg [3][i], HIGH);
    }
            server.sendHeader("Location", "/");
    server.send(302, "text/plain", ""); // 302 y send Header para que no me quede en /header 
  });

    server.on("/4",[]{
    for (int i = 0; i <= 7; i++)
    {
        digitalWrite(dis7seg [4][i], HIGH);
    }
            server.sendHeader("Location", "/");
    server.send(302, "text/plain", ""); // 302 y send Header para que no me quede en /header 
  });

    server.on("/5",[]{
    for (int i = 0; i <= 7; i++)
    {
        digitalWrite(dis7seg [5][i], HIGH);
    }
            server.sendHeader("Location", "/");
    server.send(302, "text/plain", ""); // 302 y send Header para que no me quede en /header 
  });

      server.on("/6",[]{
    for (int i = 0; i <= 7; i++)
    {
        digitalWrite(dis7seg [6][i], HIGH);
    }
            server.sendHeader("Location", "/");
    server.send(302, "text/plain", ""); // 302 y send Header para que no me quede en /header 
  });

      server.on("/7",[]{
    for (int i = 0; i <= 7; i++)
    {
        digitalWrite(dis7seg [7][i], HIGH);
    }
            server.sendHeader("Location", "/");
    server.send(302, "text/plain", ""); // 302 y send Header para que no me quede en /header 
  });

      server.on("/8",[]{
    for (int i = 0; i <= 7; i++)
    {
        digitalWrite(dis7seg [8][i], HIGH);
    }
            server.sendHeader("Location", "/");
    server.send(302, "text/plain", ""); // 302 y send Header para que no me quede en /header 
  });

      server.on("/9",[]{
    for (int i = 0; i <= 7; i++)
    {
        digitalWrite(dis7seg [9][i], HIGH);
    }
            server.sendHeader("Location", "/");
    server.send(302, "text/plain", ""); // 302 y send Header para que no me quede en /header 
  });
}
void loop(){

   server.handleClient();

   
    
}