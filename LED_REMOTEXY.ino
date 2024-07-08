#define REMOTEXY__DEBUGLOG 
#define REMOTEXY_MODE__WIFI_POINT

#include <WiFi.h>
#include <RemoteXY.h>

// Définir les informations de connexion WiFi pour RemoteXY
#define REMOTEXY_WIFI_SSID "RemoteXY"
#define REMOTEXY_WIFI_PASSWORD "12345678"
#define REMOTEXY_SERVER_PORT 6377
// Définir la broche GPIO à laquelle est connectée la LED
#define LED_PIN 2  // Exemple : GPIO 2 pour la LED

// Déclaration des variables pour RemoteXY
#pragma pack(push, 1)
uint8_t RemoteXY_CONF[] =
  { 255,1,0,0,0,45,0,17,0,0,0,69,1,106,200,1,1,2,0,129,
    15,34,74,16,204,76,69,68,32,66,76,85,69,32,0,10,27,70,49,23,
    49,4,26,31,79,78,0,31,79,70,70,0 };
struct {
  uint8_t pushSwitch_01; // État du bouton sur l'interface RemoteXY
  uint8_t connect_flag;  // Drapeau de connexion (non utilisé dans cet exemple)
} RemoteXY;
#pragma pack(pop)

void setup() {
  Serial.begin(115200);

  // Initialisation de RemoteXY
  RemoteXY_Init();

  // Définir la broche de la LED comme sortie
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  // Gérer les événements et les mises à jour de RemoteXY
  RemoteXY_Handler ();

  // Contrôler la LED en fonction de l'état du bouton RemoteXY
  if (RemoteXY.pushSwitch_01 == 1) {
    digitalWrite(LED_PIN, HIGH);  // Allumer la LED
  } else {
    digitalWrite(LED_PIN, LOW);   // Éteindre la LED
  }

  // Utiliser RemoteXY_delay() au lieu de delay() pour éviter les blocages
  RemoteXY_delay(10);
}
