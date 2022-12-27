#include <LiquidCrystal_I2C.h> // https://github.com/johnrickman/LiquidCrystal_I2C
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "<SSID>";
const char* password = "<PASSWORD>";

// pinout
//
// left YL-63
// OUT - D6
// GND - GND
// VCC - 3V3
//
// right YL-63
// OUT - D5
// GND - GND
// VCC - 3V3
//
// I2C atached to 1602
// GND - GND
// VCC - Vin
// SDA - D2
// SCL - D1

const char* host = "https://visitr.vercel.app/api";
const char* fingerpr = "44 60 CD A9 32 C1 0C F3 82 97 9A 68 50 1F BB DB 2B 12 B4 6E";
 

WiFiClientSecure client;


LiquidCrystal_I2C LCD (0x27, 16, 2);

#define L_YL63 12
#define R_YL63 14
#define BUZZER 9

#define isLempty digitalRead(L_YL63)
#define isRempty digitalRead(R_YL63)

void print00(int startIndex, int rowIndex, int num) {
  if (num < 0 || num >= 10) {
    LCD.setCursor(startIndex, rowIndex);
    LCD.print(num);
  } else {
    LCD.setCursor(startIndex, rowIndex);
    LCD.print(0);
    LCD.setCursor(startIndex + 1, rowIndex);
    LCD.print(num);
  }
}

int visitors = 0;
#define maxVisitors 3

void getRoomParams() {
  HTTPClient http;
 
  http.begin(client, host + "/rooms/1");

  int httpResponseCode = http.GET();

  Serial.println(httpResponseCode);
  String payload = http.getString();
  Serial.println(payload); 
    
  http.end();
}

void sendVisit(bool isEnter) {
  HTTPClient http;
 
  http.begin(wifiClient, host + "/visits");
  http.addHeader("Content-Type", "application/json");

  if(isEnter) {
    Serial.print("Sending enter...\n");
  } else {
    Serial.print("Sending exit...\n");
  }
  char* isEnterSerialised = isEnter ? "true" : "false";
  int httpResponseCode = http.POST("{\"room_id\": 1, \"is_enter\":" + isEnterSerialised + "}");

  Serial.println(httpResponseCode);
  String payload = http.getString();
  Serial.println(payload);  
    
  http.end();
}

void setup() {
  pinMode(L_YL63, INPUT);
  pinMode(R_YL63, INPUT);
  pinMode(BUZZER, OUTPUT);

  WiFi.begin(ssid, password);
  Serial.begin(9600);

  LCD.init();
  LCD.backlight();

  LCD.setCursor(0, 0);
  LCD.print("Connecting WiFI");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print("Connecting...\n");
  }
  LCD.setCursor(0, 0);
  LCD.print("Visitors: 00/??");

  if (WiFi.status() == WL_CONNECTED) {
    client.setFingerprint(fingerpr);
  }

  getRoomParams();
}

void loop() {

  print00(10, 0, visitors);
  print00(13, 0, maxVisitors);

  if (visitors == maxVisitors) {
    LCD.setCursor(0, 1);
    LCD.print("limit     ");
  } else if (visitors > maxVisitors) {
    LCD.setCursor(0, 1);
    tone(BUZZER, 230, 150);
    LCD.print("OVERLIMIT!");
  } else {
    LCD.setCursor(0, 1);
    LCD.print("          ");
  }

  if (!isLempty) {
    visitors++;

    sendVisit(true);

     delay(1000);
     return;
  } else if (!isRempty) {
    visitors--;

    sendVisit(false);

     delay(1000);
  }
}
