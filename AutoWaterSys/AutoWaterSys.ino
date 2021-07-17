 /////////////////////////////////
// Generated with a lot of love//
// with TUNIOT FOR ESP8266     //
// Website: Easycoding.tn      //
/////////////////////////////////
#include <ESP8266WiFi.h>

#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883
#define AIO_USERNAME  "fatsfish"
#define AIO_KEY  "aio_urXk57GjAWX7xzb6Pv11lR75HITl"
WiFiClient client;

Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

Adafruit_MQTT_Subscribe myWateringSystem = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/myWateringSystem");
String  request;
boolean MQTT_connect();

boolean MQTT_connect() {  int8_t ret; if (mqtt.connected()) {    return true; }  uint8_t retries = 3;  while ((ret = mqtt.connect()) != 0) { mqtt.disconnect(); delay(2000);  retries--;if (retries == 0) { return false; }} return true;}

void setup()
{
  Serial.begin(9600);
request = "";

pinMode(2, OUTPUT);
  WiFi.disconnect();
   WiFi.begin("3chuMeocon","dentrangvang");
  while ((!(WiFi.status() == WL_CONNECTED))){
    delay(300);
    Serial.print("");

  }
  Serial.println("connected!");
  Serial.println((WiFi.localIP().toString()));

  mqtt.subscribe(&myWateringSystem);

}


void loop()
{

    if (MQTT_connect()) {
      Adafruit_MQTT_Subscribe *subscription_name;
      while ((subscription_name = mqtt.readSubscription(5000))) {
        if (subscription_name == &myWateringSystem) {
          request = ((char *)myWateringSystem.lastread);

        }
        if (request == "on") {
          digitalWrite(2,LOW);
          Serial.println("System on");

        }
        if (request == "off") {
          digitalWrite(2,HIGH);
          Serial.println("System off");

        }

      }

    }

}
