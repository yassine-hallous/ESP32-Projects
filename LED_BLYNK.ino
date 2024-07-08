#define BLYNK_TEMPLATE_ID "TMPL22K_LyAK2"
#define BLYNK_TEMPLATE_NAME "LED ON OFF"
#define BLYNK_AUTH_TOKEN "GrImteLrTp3klZ9B2Ihs_YPI0tjH4ktU"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

// Identifiants du réseau WiFi
const char* ssid = "Galaxy A14 2869";
const char* password = "kzt9qeau6yxtbnx";

// Jeton d'authentification Blynk
char auth[] = "GrImteLrTp3klZ9B2Ihs_YPI0tjH4ktU";

// Broche à laquelle est connectée la LED
#define LED_PIN 2  // GPIO 2 pour la LED

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);  // Définition de la broche de la LED comme sortie

  // Connexion au réseau WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connexion au WiFi en cours...");
  }
  Serial.println("Connecté au WiFi");

  // Initialisation de la connexion Blynk
  Blynk.begin(auth, ssid, password);
}

void loop() {
  Blynk.run();  // Gestion des communications Blynk
}

// Fonction appelée lorsque l'état du bouton sur Blynk change
BLYNK_WRITE(V1) {
  int pinValue = param.asInt();  // Lecture de la valeur du bouton de l'application Blynk
  if (pinValue == 1) {
    digitalWrite(LED_PIN, HIGH);  // Allumer la LED
    Serial.println("LED allumée");
  } else {
    digitalWrite(LED_PIN, LOW);   // Éteindre la LED
    Serial.println("LED éteinte");
  }
}
