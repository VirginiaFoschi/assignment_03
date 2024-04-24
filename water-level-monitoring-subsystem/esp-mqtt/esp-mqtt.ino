#include <WiFi.h>
#include <PubSubClient.h>
#include "Sonar.h"
#include "Led.h"
#define MSG_BUFFER_SIZE  50


// Pin configurations
const int ledPinG = 27;  // Green LED pin
const int ledPinR = 25;  // Red LED pin
const int triggerPin = 12; // Sonar trigger pin
const int echoPin = 13; // Sonar echo pin

Sonar *sonar = new Sonar(triggerPin, echoPin);
Led *ledG = new Led(ledPinG);
Led *ledR = new Led(ledPinR);

/* wifi network info */

const char* ssid = "EOLO_082229";
const char* password = "hX9kpatJ8";
/* MQTT server address */
const char* mqtt_server = "broker.mqtt-dashboard.com";

/* MQTT topic */
const char* topicWater = "esiot-2023-waterLevel";
const char* topicFreq = "esiot-2023-freq";

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
/*We can get the current frequence*/
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.println(String("Message arrived on [") + topic + "] len: " + length );

  char message[length + 1]; // Alloca un array di caratteri di dimensione sufficiente a contenere il payload più il carattere null
  memcpy(message, payload, length); // Copia il payload nell'array 'message'
  message[length] = '\0'; // Imposta il carattere terminatore di stringa

  int value = atoi(message);
  currentFrequence = value;
  Serial.println(currentFrequence);
  
}

bool reconnect() {
  
  // Loop until we're reconnected
  
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    
    // Create a random client ID
    String clientId = String("esiot-2122-client-")+String(random(0xffff), HEX);

    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      client.subscribe(topicFreq);
      return true;
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
      return false;
    }
  }
}

bool readDistance() {
  float distance = sonar->getDistance();
    /* creating a msg in the buffer */
  snprintf (msg, MSG_BUFFER_SIZE, "Distance: %f", distance);

  Serial.println(String("Publishing message: ") + msg);
    
    /* publishing the msg */
  return client.publish(topicWater, msg);  
}

void controllSendData() {
  unsigned long now = millis();
  if (now - lastMsgTime > currentFrequence) {
    lastMsgTime = now;  
    if (reconnect() && readDistance()) {
      ledG->turnOn();
      ledR->turnOff();
    }
    else {
      ledR->turnOn();
      ledG->turnOff();
    }
      
  }
}


void setup() {
  Serial.begin(115200);
  setup_wifi();
  randomSeed(micros());
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  controllSendData();
}
