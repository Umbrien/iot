#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>


const char* ssid = "<YOUR_SSID>";
const char* password = "<YOUR_PASSWORD>";

WiFiClient wifiClient;


void setup () {
 
  Serial.begin(9600);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
 
    delay(1000);
    Serial.print("Connecting...\n");
  }
}
 
void loop() {
 
  if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
 
    HTTPClient http;  //Declare an object of class HTTPClient
 
    http.begin(wifiClient, "http://jsonplaceholder.typicode.com/users/1");  //Specify request destination
    int httpCode = http.GET();                                  //Send the request
 
    if (httpCode > 0) { //Check the returning code
 
      String payload = http.getString();   //Get the request response payload
      Serial.println(payload);             //Print the response payload
    }
 
    http.end();   //Close connection
  }
 
  delay(30000);    //Send a request every 30 seconds
}
