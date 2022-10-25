//code Node mcu ครับ

#include <WiFiManager.h>
const char* host = "tongza.000webhostapp.com";
#define Control_RS485_PIN 5
bool onswitch[5], off[5]; 
unsigned long timedelay[5];
unsigned long t[5];
int Motor_Start, k = 0;
String comString = "";
//WiFiClient client;
void setup() {
  comString.reserve(258);
  Serial.begin(9600);
//  WiFi.mode(WIFI_STA);
//  WiFiManager wm;
//  bool res;
//  res = wm.autoConnect("sontaya"); // anonMotor_Startmous ap
//  // res = wm.autoConnect("AutoConnectAP", "password"); // password protected ap
//  // ESP.restart();
//  //  if (!res)  Serial.println("Failed to connect");
//  //  else
  
  pinMode(Control_RS485_PIN, OUTPUT);
  digitalWrite(Control_RS485_PIN, LOW);
}
void loop() {
  
  while (Serial.available()>0){
    if (Serial.available()>0){
      serialEvent();
      break;
    }
  }
  if (onswitch[0]){
    if (!off[0]){
      if (CheckMotor()){
        if (millis() - t[0] >= timedelay[0]) {
          t[0] = millis();
          digitalWrite(Control_RS485_PIN, HIGH);
          Serial.println("1o"); 
          digitalWrite(Control_RS485_PIN, LOW);
          phplogging("1");
          off[0] = 1;
        }
      } else {
        digitalWrite(Control_RS485_PIN, HIGH);
        Serial.println("1o"); 
        digitalWrite(Control_RS485_PIN, LOW);
        phplogging("1");
        off[0] = 1;
      }
    }
  } else {
    t[0] = millis();
  }
  if (onswitch[1]) {
    if (!off[1]) {
      if (CheckMotor()) {
        if (millis() - t[1] >= timedelay[1]) {
          t[1] = millis();
          digitalWrite(Control_RS485_PIN, HIGH);
          Serial.println("2o");
          digitalWrite(Control_RS485_PIN, LOW);
          phplogging("2");
          off[1] = 1;
        }
      } else {
        digitalWrite(Control_RS485_PIN, HIGH);
        Serial.println("2o");
        digitalWrite(Control_RS485_PIN, LOW);
        phplogging("2");
        off[1] = 1;
      }
    }
  } else {
    t[1] = millis();
  }
}
void serialEvent() {
  while (Serial.available()>0) {
    char inChar = (char)Serial.read();
    comString += inChar;
    Serial.println("input: "+(String)comString);
    if (inChar == '\n') {
      comString.trim(); 
      if (comString[0] == '!' and comString[1] == '1'){
        delay(100);
        onmotor(0);
      }
      if (comString[0] == 'c' and comString[1] == '1') offmotor(0);
      if (comString[0] == '!' and (comString[1] & 0x0f) == 2) onmotor(1);
      if (comString[0] == 'c' and (comString[1] & 0x0f) == 2) offmotor(1);
      if (comString[0] == 'e' and (comString[1] & 0x0f) == 1) phplogging("e1");
      if (comString[0] == 'e' and (comString[1] & 0x0f) == 2) phplogging("e2");
      comString = "";
    }
  }
}

void onmotor(int i) {
  onswitch[i] = 1;
  timedelay[i] = settimedelay();
  off[i] = 0;
  Motor_Start++;
}
void offmotor(int i) {
  onswitch[i] = 0;
  Motor_Start--;
  i += 1;
  phplogging("-" + (String)i);
}
unsigned long settimedelay() {
  return Motor_Start * 4000;
}

bool CheckMotor() {
  return Motor_Start - 1 > 0;
}

void phplogging(String num) {
//  if (!client.connect(host, 80)) {
//    return;
//  } else {
//    //    Serial.println("--- connection success !!! ---");
//  }
//  String url = "/datalogger.php?case=" + num; //ชุด DirectorMotor_Start ที่เก็บไฟล์ และตัวแปรที่ต้องการจะฝาก
//  //ส่งค่าตัวแปร
//  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
//               "Host: " + host + "\r\n" +
//               "Connection: close\r\n\r\n");

}
