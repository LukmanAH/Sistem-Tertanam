const int button1=2;
const int button2=3;
const int button3=4;
const int ledbiru=5;
const int ledkuning=6;
const int ledmerah=7;
int kondisi=0;

void setup() {
//mendklarasikan pin 2 sebagai INPUT dengan PullUP Resistor
pinMode(button1, INPUT_PULLUP);
pinMode(button2, INPUT_PULLUP);
pinMode(button3, INPUT_PULLUP);
pinMode(11, OUTPUT);
pinMode(ledkuning, OUTPUT);
pinMode(ledbiru, OUTPUT);
pinMode(ledmerah, OUTPUT);
}

void loop() {
int sensorValue1 = digitalRead(button1);
int sensorValue2 = digitalRead(button2);
int sensorValue3 = digitalRead(button3);

if (sensorValue3 == LOW) {
    kondisi+=5;
   if(kondisi<25){
    digitalWrite(ledbiru, LOW);
    delay(500);
    digitalWrite(ledbiru, HIGH);
    delay(500);
   }else if(kondisi<50){
     digitalWrite(ledkuning, HIGH);
     delay(500);
     digitalWrite(ledkuning, LOW);
     delay(500);
   }else if(kondisi>50){
     digitalWrite(ledmerah, HIGH);
     delay(500);
     digitalWrite(ledmerah, LOW);
     delay(500);
   }
}else if (sensorValue3 == HIGH && kondisi <25  && kondisi >= 7) {
    kondisi=5;
}else if(sensorValue3 == HIGH && kondisi>=25 && kondisi<50) {
    kondisi=6;
}else if(kondisi>=50){
  kondisi=0;
}else if (sensorValue1 == LOW && kondisi!=4) {
    delay(300);
    kondisi=4;
}else if(sensorValue1 == LOW && kondisi==4) {
    delay(300);
    kondisi=0;
}else if(kondisi > 5 && sensorValue2 == LOW){
  kondisi=0;
  delay(500);
}else if(sensorValue2 == LOW ){
  kondisi++;
  delay(500);
}

switch(kondisi){
  case 0:
  digitalWrite(ledbiru, LOW);
  digitalWrite(ledkuning, LOW);
  digitalWrite(ledmerah, LOW);
  digitalWrite(11, LOW);
  break; 
  
  case 1:
    digitalWrite(ledbiru, HIGH);
    digitalWrite(11, HIGH);
    delay(100);
    digitalWrite(ledbiru, LOW);
    digitalWrite(11, LOW);
    delay(800);
  break;

   case 2:
    digitalWrite(ledkuning, HIGH);
    digitalWrite(11, HIGH);
    delay(100);
        digitalWrite(ledkuning, LOW);
    digitalWrite(11, LOW);
    delay(400);
  break;

   case 3:
    digitalWrite(ledmerah, HIGH);
    digitalWrite(11, HIGH);
    delay(100);
    digitalWrite(ledmerah, LOW);
    digitalWrite(11, LOW);
    delay(200);
  break;

  case 4:
    digitalWrite(ledkuning, HIGH);
    digitalWrite(ledmerah, HIGH);
    digitalWrite(ledbiru, HIGH);
    digitalWrite(11, HIGH);
  break;

   case 5:
    digitalWrite(ledbiru, HIGH);
    delay(300);
    digitalWrite(ledbiru, LOW);
    digitalWrite(ledkuning, HIGH);
    delay(300);
    digitalWrite(ledkuning, LOW);
    digitalWrite(ledmerah, HIGH);
    delay(300);
    digitalWrite(ledmerah, LOW);
    digitalWrite(11, HIGH);
    delay(100);
    digitalWrite(11, LOW);
    
  break;
  
 case 6:
    digitalWrite(ledbiru, HIGH);
    delay(100);
    digitalWrite(ledbiru, LOW);
    digitalWrite(ledkuning, HIGH);
    delay(100);
    digitalWrite(ledkuning, LOW);
    digitalWrite(ledmerah, HIGH);
    delay(100);
    digitalWrite(ledmerah, LOW);
    digitalWrite(11, HIGH);
    delay(100);
    digitalWrite(11, LOW);
    
  break;
}
}
