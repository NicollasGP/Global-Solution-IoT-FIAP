#include <WiFi.h>
#include <PubSubClient.h>

// WiFi
constexpr const char* SSID = "Wokwi-GUEST";
constexpr const char* PASSWORD = "";

// MQTT
constexpr const char* MQTT_SERVER = "broker.hivemq.com";
constexpr const char* TOPIC_NIVEL = "hidrosafe/sensor/nivel";

// Pinos
constexpr int TRIG_PIN = 19;
constexpr int ECHO_PIN = 18;
constexpr int RED_PIN = 21;
constexpr int GREEN_PIN = 22;
constexpr int BUZZER_PIN = 13;

WiFiClient espClient;
PubSubClient mqttClient(espClient);

enum NivelAgua { NORMAL, ATENCAO, CRITICO };

void conectarWiFi() {
  Serial.print("Conectando ao WiFi ");
  Serial.println(SSID);
  WiFi.begin(SSID, PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi conectado. IP: " + WiFi.localIP().toString());
}

void conectarMQTT() {
  while (!mqttClient.connected()) {
    Serial.print("Conectando ao MQTT...");
    if (mqttClient.connect("ESP32_HidroSafe")) {
      Serial.println("Conectado!");
    } else {
      Serial.print("Erro: ");
      Serial.print(mqttClient.state());
      Serial.println(" Tentando novamente em 5s...");
      delay(5000);
    }
  }
}

long medirDistanciaCM() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  return pulseIn(ECHO_PIN, HIGH) * 0.034 / 2;
}

NivelAgua determinarNivel(long cm) {
  if (cm < 10) return NORMAL;
  if (cm <= 20) return ATENCAO;
  return CRITICO;
}

void atualizarLED(NivelAgua nivel) {
  switch (nivel) {
    case NORMAL:
      digitalWrite(RED_PIN, LOW);
      digitalWrite(GREEN_PIN, HIGH);
      break;
    case ATENCAO:
      digitalWrite(RED_PIN, HIGH);
      digitalWrite(GREEN_PIN, HIGH);
      break;
    case CRITICO:
      digitalWrite(RED_PIN, HIGH);
      digitalWrite(GREEN_PIN, LOW);
      break;
  }
}

void buzinar(NivelAgua nivel) {
  nivel == CRITICO ? tone(BUZZER_PIN, 1000) : noTone(BUZZER_PIN);
}

const char* nivelToString(NivelAgua nivel) {
  switch (nivel) {
    case NORMAL: return "Normal";
    case ATENCAO: return "Atenção";
    case CRITICO: return "CRÍTICO!!!!";
    default: return "";
  }
}

void setup() {

  Serial.begin(115200);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  conectarWiFi();
  mqttClient.setServer(MQTT_SERVER, 1883);
  
}

void loop() {

  if (!mqttClient.connected()) conectarMQTT();
  mqttClient.loop();

  long distancia = medirDistanciaCM();
  NivelAgua nivel = determinarNivel(distancia);

  atualizarLED(nivel);
  buzinar(nivel);

  // Converte enum NivelAgua para string
  const char* nivelStr = nivelToString(nivel);

  // Monta JSON com distância e nível
  char payload[150];
  sprintf(payload, "{\"distancia\": %ld, \"nivel\": \"%s\"}", distancia, nivelStr);

  mqttClient.publish(TOPIC_NIVEL, payload);

  Serial.printf("Mensagem MQTT enviada: %s\n", payload);

  delay(3000);

}
