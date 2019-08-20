#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ThingSpeak.h>

String apiWritekey = "Q9S9I28NT7T0RZOO";
#define CHANNEL_ID  568755; 
const char* ssid = "**********";
const char* password = "*********";
 
const char* server = "api.thingspeak.com";
float resolution=3.3/1024;
WiFiClient client;
 
void setup() {
  Serial.begin(115200);
  WiFi.disconnect();
  delay(10);
  WiFi.begin(ssid, password);
 
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
   
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("NodeMcu connected to wifi...");
  Serial.println(ssid);
  Serial.println();
}
 
void loop() {
  float temp = ((analogRead(A0) * resolution) * 100)-4;    // -4 for adjusting tolerence
  if (client.connect(server,80))
  {  
    String tsData = apiWritekey;
           tsData +="&field1=";
           tsData += String(temp);
           tsData += "\r\n\r\n";
 
     client.print("POST /update HTTP/1.1\n");
     client.print("Host: api.thingspeak.com\n");
     client.print("Connection: close\n");
     client.print("X-THINGSPEAKAPIKEY: "+apiWritekey+"\n");
     client.print("Content-Type: application/x-www-form-urlencoded\n");
     client.print("Content-Length: ");
     client.print(tsData.length());
     client.print("\n\n");
     client.print(tsData);
 
     Serial.print("Temperature: ");
     Serial.print(temp);
     Serial.println("uploaded to Thingspeak server....");
  }
  client.stop();
 
  Serial.println("Waiting to upload next reading...");
  Serial.println();
    delay(15000);
}
