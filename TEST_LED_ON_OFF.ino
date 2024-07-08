#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "Galaxy A14 2869";
const char* password = "kzt9qeau6yxtbnx";

WebServer server(80);

const int ledPin = 2;

void setup() {
  Serial.begin(115200);
  delay(1000);  // Allow serial communication to establish

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);  // Ensure LED is initially off

  server.on("/", HTTP_GET, []() {
    String html = "<html><head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">";
    html += "<script>function sendRequest(url) { var xhr = new XMLHttpRequest(); xhr.open('GET', url, true); xhr.send(); }</script>";
    html += "</head><body style=\"font-family: Arial, sans-serif; text-align: center;\">";
    
    // Styles des boutons
    html += "<style>.button { padding: 10px 20px; font-size: 18px; text-decoration: none; margin: 10px; cursor: pointer; border-radius: 5px; }";
    html += ".button-on { background-color: #4CAF50; color: white; } .button-off { background-color: #f44336; color: white; }</style>";

    // Contenu de la page
    html += "<h1>Serveur Web ESP32</h1>";
    html += "<div>";
    html += "<button class=\"button button-on\" onclick=\"sendRequest('/on')\">Allumer la LED</button>";
    html += "<button class=\"button button-off\" onclick=\"sendRequest('/off')\">Eteindre la LED</button>";
    html += "<p id=\"statusMessage\"></p>";
    html += "</div>";

    // Script JavaScript pour mettre à jour le message d'état
    html += "<script>function updateStatusMessage(message) { document.getElementById('statusMessage').textContent = message; }</script>";

    html += "</body></html>";
    server.send(200, "text/html", html);
  });

  server.on("/on", HTTP_GET, []() {
    digitalWrite(ledPin, HIGH);  // Allumer la LED
    server.send(200, "text/plain", "LED allumée");
    delay(100);  // Délai pour laisser le temps à la réponse de se terminer
  });

  server.on("/off", HTTP_GET, []() {
    digitalWrite(ledPin, LOW);  // Éteindre la LED
    server.send(200, "text/plain", "LED éteinte");
    delay(100);  // Délai pour laisser le temps à la réponse de se terminer
  });

  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}
