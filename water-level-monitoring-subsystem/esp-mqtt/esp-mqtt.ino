#include <WiFi.h>
#include <PubSubClient.h>
#define MSG_BUFFER_SIZE  50

// Pin configurations
const int ledPinG = 4;  // Green LED pin
const int ledPinR = 5;  // Red LED pin
const int echoPin = 18;
const int triggerPin = 17;
const float temperature = 20;
const float vs = 331.45 + 0.62 * temperature;


/* wifi network info */

const char* ssid = "Davide wifi";
const char* password = "davide2024";

/* MQTT server address */
const char* mqtt_server = "broker.mqtt-dashboard.com";

/* MQTT topic */
const char* topicFreq = "esiot-2023Freq";
const char* topicSonar = "esiot-2023Sonar";

/* MQTT client management */

WiFiClient espClient;
PubSubClient client(espClient);


unsigned long lastMsgTime = 0;
unsigned int currentFrequence = 2000;
char msg[MSG_BUFFER_SIZE];


void setup_wifi() {

  delay(10);

  Serial.println(String("Connecting to ") + ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

/* MQTT subscribing callback */

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.println(String("Message arrived on [") + topic + "] len: " + length );
  char message[length + 1]; // Alloca un array di caratteri di dimensione sufficiente a contenere il payload più il carattere null
  memcpy(message, payload, length); // Copia il payload nell'array 'message'
  message[length] = '\0'; // Imposta il carattere terminatore di stringa

  int value = atoi(message);
  currentFrequence = value;
  Serial.println(value);
}

void reconnect() {
  
  // Loop until we're reconnected
  
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    
    // Create a random client ID
    String clientId = String("esiot-2122-client-")+String(random(0xffff), HEX);

    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      // client.publish("outTopic", "hello world");
      // ... and resubscribe
      client.subscribe(topicFreq);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
      
    }
  }
}

float getDistance()
{
    /* Triggering stage: sending the impulse */
    digitalWrite(triggerPin, LOW);
    delayMicroseconds(3);
    digitalWrite(triggerPin, HIGH);
    delayMicroseconds(5);
    digitalWrite(triggerPin, LOW);

    /* Receiving the echo */
    float tUS = pulseIn(echoPin, HIGH);
    float t = tUS / 1000.0 / 1000.0 / 2;
    float d = t * vs;
    return d * 100;
}

void setup() {
  Serial.begin(9600);
  pinMode(ledPinG, OUTPUT);
  pinMode(ledPinR, OUTPUT);
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
  setup_wifi();
  randomSeed(micros());
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

bool sendMessage() {
  /* creating a msg in the buffer */
    snprintf (msg, MSG_BUFFER_SIZE, "%f", getDistance());

    Serial.println(String("Publishing message: ") + msg);
    
    /* publishing the msg */
    return client.publish(topicSonar, msg);
}

void loop() {

  if (!client.connected()) {
    digitalWrite(ledPinR, HIGH);
    digitalWrite(ledPinG, LOW);
    reconnect();
  }
  else {
    digitalWrite(ledPinR, LOW);
    digitalWrite(ledPinG, HIGH);
  }
  client.loop();

  unsigned long now = millis();
  if (now - lastMsgTime > currentFrequence) {
    lastMsgTime = now;

    if(sendMessage()) {
      digitalWrite(ledPinR, LOW);
      digitalWrite(ledPinG, HIGH);
    }else {
      digitalWrite(ledPinR, HIGH);
      digitalWrite(ledPinG, LOW);
    }
      
  }
}
