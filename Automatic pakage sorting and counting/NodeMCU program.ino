#include <FirebaseESP8266.h>
#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>
#include <ArduinoJson.h>

#define FIREBASE_HOST "https://iot-tubes-c8593-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "LVk09ghR07N5QxbzrX03nk1cAVaLUImfhXtqb33Y"
#define WIFI_SSID "mamang"
#define WIFI_PASSWORD "imad1234"
#define txPin D5
#define rxPin D6

FirebaseData firebaseData;
FirebaseJson json;
SoftwareSerial ss(rxPin,txPin);
String path;
StaticJsonDocument<1000> root_val;

void setup() {
  Serial.begin(9600);
  ss.begin(9600);
  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);

  firebaseData.setBSSLBufferSize(1024, 1024);
  firebaseData.setResponseSize(1024);

  Firebase.setReadTimeout(firebaseData, 1000 * 60);
  Firebase.setwriteSizeLimit(firebaseData, "tiny");

  Firebase.setFloatDigits(2);
  Firebase.setDoubleDigits(6);
}

void loop() {
  DeserializationError error = deserializeJson(root_val, ss);

  if(ss.available() > 0) Serial.println("Serial ada");

  if(error) return;

  if(root_val["tanggal"] == nullptr) return;
  else if(root_val["bb"] == nullptr) return;
  else if(root_val["bk"] == nullptr) return;
  
  String tanggal = root_val["tanggal"];
  String bb = root_val["bb"];
  String bk = root_val["bk"];
  path = "Tanggal : " + tanggal;

  if(Firebase.set(firebaseData, path + "/Barang besar", bb)){
    Serial.println("PASSED");
    }
  else{
    Serial.println("FAILED");
  }
  if(Firebase.set(firebaseData, path + "/Barang kecil", bk)){
    Serial.println("PASSED");
  }
  else{
    Serial.println("FAILED");
  }
}
