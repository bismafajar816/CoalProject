#include <WiFi.h>
#include <PubSubClient.h>
#include <HTTPClient.h>

// WiFi
const char *ssid = "OPPO A5 2020";   // Enter your Wi-Fi name
const char *password = "waliahmad";  // Enter Wi-Fi password

// MQTT Broker
const char *mqtt_broker = "test.mosquitto.org";
const char *topic = "rgb";
const char *mqtt_username = "";
const char *mqtt_password = "";
const int mqtt_port = 1883;

// ThingSpeak
const char *thingSpeakApiKey = "BLVZ15542DF9TI7K";
const char *thingSpeakUrl = "http://api.thingspeak.com/update?api_key=";

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  Serial.begin(9600);
  WiFi.mode(WIFI_STA);
  WiFi.onEvent(ConnectedToAP_Handler, ARDUINO_EVENT_WIFI_STA_CONNECTED);
  WiFi.onEvent(GotIP_Handler, ARDUINO_EVENT_WIFI_STA_GOT_IP);
  WiFi.onEvent(WiFi_Disconnected_Handler, ARDUINO_EVENT_WIFI_STA_DISCONNECTED);
  WiFi.begin(ssid, password);
  Serial.println("Connecting to WiFi Network ..");
  //connecting to an MQTT broker
  client.setServer(mqtt_broker, mqtt_port);
  client.setCallback(callback);
  while (!client.connected()) {
    String client_id = "esp32-client-";
    client_id += String(WiFi.macAddress());
    Serial.printf("The client %s connects to the public MQTT broker\n", client_id.c_str());
    if (client.connect(client_id.c_str(), mqtt_username, mqtt_password)) {
      Serial.println("Public EMQX MQTT broker connected");
    } else {
      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);
    }
  }

  client.subscribe(topic);
}

void callback(char *topic, byte *payload, unsigned int length) {
  for (int i = 0; i < length; i++) {
    Serial.write((char)payload[i]);
    sendDataToThingSpeak(String((char)payload[i]));  // Send data to ThingSpeak
  }
  Serial.println();
}

void loop() {
  client.loop();
  delay(2000);
}

void ConnectedToAP_Handler(WiFiEvent_t wifi_event, WiFiEventInfo_t wifi_info) {
  Serial.println("Connected To The WiFi Network");
}

void GotIP_Handler(WiFiEvent_t wifi_event, WiFiEventInfo_t wifi_info) {
  Serial.print("Local ESP32 IP: ");
  Serial.println(WiFi.localIP());
}

void WiFi_Disconnected_Handler(WiFiEvent_t wifi_event, WiFiEventInfo_t wifi_info) {
  Serial.println("Disconnected From WiFi Network");
  // Attempt Re-Connection
  WiFi.begin(ssid, password);
}

void sendDataToThingSpeak(String data) {
  // Create a HTTP client object
  HTTPClient http;
  // Construct the ThingSpeak URL with your API key and data
  String url = "";

  if (data == "1") {
    url = String(thingSpeakUrl) + String(thingSpeakApiKey) + "&field1=" + "1" + "&field2=" + "1" + "&field3=" + "0"+ "&field4=" + "0";
  }
  if (data == "2") {
    url = String(thingSpeakUrl) + String(thingSpeakApiKey) + "&field1=" + "1" + "&field2=" + "0" + "&field3=" + "1"+ "&field4=" + "0";
  }
  if (data == "3") {
    url = String(thingSpeakUrl) + String(thingSpeakApiKey) + "&field1=" + "1" + "&field2=" + "1" + "&field3=" + "1"+ "&field4=" + "0";
  }
  if (data == "4") {
    url = String(thingSpeakUrl) + String(thingSpeakApiKey) + "&field1=" + "0" + "&field2=" + "0" + "&field3=" + "0"+ "&field4=" + "1";
  }
  if (data == "5") {
    url = String(thingSpeakUrl) + String(thingSpeakApiKey) + "&field1=" + "0" + "&field2=" + "0" + "&field3=" + "0"+ "&field4=" + "0";
  }

  // Begin the HTTP request
  http.begin(url);

  // Send the HTTP GET request
  int httpCode = http.GET();

  // Check the HTTP response code
  if (httpCode == HTTP_CODE_OK) {
    Serial.println("Data sent to ThingSpeak successfully");
  } else {
    Serial.print("Failed to send data to ThingSpeak. HTTP code: ");
    Serial.println(httpCode);
  }

  // End the HTTP request
  http.end();
}
