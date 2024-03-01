#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include "index.h" //Our HTML webpage contents with javascripts
//#include "DHTesp.h" //DHT11 Library for ESP
#define LED D7 //On board LED
//#define DHTpin 14 //D5 of NodeMCU is GPIO14
//DHTesp dht;
// Replace with your SSID and Password here
const char* ssid = "AETOS";
const char* password = "9176673062";
ESP8266WebServer server(80); //Server on port 80
void handleRoot() {
String s = MAIN_page; //Read HTML contents
server.send(200, "text/html", s); //Send web page
}
//float humidity, temperature;
void handleADC() {
int rain = analogRead(A0);
//Create JSON data
//String data = "{\"Rain\":\""+String(rain)+"\", \"Temperature\":\""+ String(temperature) +"\", \"Humidity\":\""+ String(humidity) +"\"}";
String data = "{\"Rain\":\""+String(rain)+"\"}";
digitalWrite(LED,!digitalRead(LED));
server.send(200, "text/plane", data);

Serial.print("R:");
Serial.println(rain);
}
void setup()
{
Serial.begin(115200);
Serial.println();
//dht.setup(DHTpin, DHTesp::DHT11); //for DHT11 Connect DHT sensor to GPIO 17
WiFi.begin(ssid, password); //Connect to your WiFi router
Serial.println("");
pinMode(LED,OUTPUT);
// Wait for connection
while (WiFi.status() != WL_CONNECTED) {
delay(500);
Serial.print(".");
}
Serial.println("");
Serial.print("Connected to ");
Serial.println(ssid);
Serial.print("IP address: ");
Serial.println(WiFi.localIP()); //IP address assigned to your ESP
server.on("/", handleRoot); //Which routine to handle at root location. This is display page
server.on("/readADC", handleADC); //This page is called by java Script AJAX
server.begin(); //Start server
Serial.println("HTTP server started");
}
void loop()
{
server.handleClient(); //Handle client requests
}