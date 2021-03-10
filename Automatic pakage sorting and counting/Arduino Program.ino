#include <RTClib.h>
#include <Wire.h>
#include <Servo.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
#include <ArduinoJson.h>

#define rxPin 5
#define txPin 6
#define trigPin 3
#define echoPin 2
#define infraPin 12
#define servoPin 11
#define buzzerPin 4

SoftwareSerial ss(rxPin,txPin);
LiquidCrystal_I2C lcd(0x27, 16, 2);
DS3231 rtc;
Servo myservo;
int bk = 0, bb = 0;

void setupRTC(){
  rtc.begin();
  rtc.adjust(DateTime(__DATE__,__TIME__));
}

void setupLCD(){
  lcd.init();
  lcd.backlight();
}

void setupSerial(){
  ss.begin(9600);
  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);
}

void setup() {
  Serial.begin(9600);
  setupSerial();
  pinMode(buzzerPin, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(infraPin, INPUT);
  myservo.attach(servoPin);
  setupRTC();
  setupLCD();
}

void main_code(int IR){
  StaticJsonDocument<1000> root_val;
  DateTime wkt = rtc.now();
  char t[16];
  int duration;
  float distance;
  bool status_barang = false;
  int new_distance;

  sprintf(t, "%02d-%02d-%02d", wkt.day(), wkt.month(), wkt.year());
  digitalWrite(trigPin,LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(trigPin,LOW);
  delayMicroseconds(5);
  duration = pulseIn(echoPin, HIGH);
  distance = duration / 58.2; // dalam cm
  new_distance = constrain(distance, 0, 23);
  
  if(new_distance <= 13) status_barang = true;
  else if(new_distance > 13 && new_distance < 23) status_barang = false;
  
  if(IR == LOW){
    if(status_barang){
     myservo.write(180);
     tone(buzzerPin, 2950, 100);
     bb += 1;
    }
    else{
     myservo.write(120);
     tone(buzzerPin, 2500, 100);
     bk += 1;
    } 
  }
  else{
    myservo.write(180);
    noTone(buzzerPin);
  }
  
  if(wkt.hour() == 0){
    bk = 0;
    bb = 0;
  }
  
  root_val["tanggal"] = String(t);
  root_val["bb"] = String(bb);
  root_val["bk"] = String(bk);

  if(ss.available() > 0){
    serializeJson(root_val, ss);
  }
  lcd_code(t, bk, bb);
}

void lcd_code(char tanggal[16],int BK, int BB){
  lcd.setCursor(0, 0);
  lcd. print(tanggal);
  lcd.setCursor(0, 1);
  lcd.print("BK : ");
  lcd.print(BK);
  lcd.print("  BB : ");
  lcd.print(BB);
}

void loop() {
  int readIR = digitalRead(infraPin);
  main_code(readIR);
  delay(500);
}
