//code Node mcu ครับ

#include <WiFiManager.h>
const char* host = "tongza.000webhostapp.com";
#define pullup INPUT_PULLUP
bool onswitch[5], off[5]; bool ti[5];
unsigned long settimedelay();
unsigned long timedelay[5];
unsigned long t[5];
int y, k = 0;
String comString = "";
WiFiClient client;
void setup() {
  comString.reserve(128);
  Serial.begin(9600);
  WiFi.mode(WIFI_STA); // explicitly set mode, esp defaults to STA+AP
  WiFiManager wm;
  bool res;
  // res = wm.autoConnect(); // auto generated AP name from chipid
  res = wm.autoConnect("sontaya"); // anonymous ap
  // res = wm.autoConnect("AutoConnectAP", "password"); // password protected ap
  // ESP.restart();

  if (!res)  Serial.println("Failed to connect");
  else  Serial.println("เชื่อมต่อแล้วค้าบบบบ ^____^");
  pinMode(5, pullup);
  pinMode(4, pullup);
      pinMode(16,OUTPUT);
}
void loop() {
  while (Serial.available()) {
    if (Serial.available() > 0) {
      serialEvent();
      break;
    }
  }
  if (onswitch[0]) {
    if (!off[0]) {
      if (c()) {
        if (millis() - t[0] >= timedelay[0]) {
          t[0] = millis();
          Serial.println("1o");
          Serial.flush();
          phplogging("1");
          off[0] = 1;
        }
      } else {
               Serial.println("1o");
               Serial.flush();
        phplogging("1");
        off[0] = 1;
      }
    }
  } else {
    t[0] = millis();
  }

  if (onswitch[1]) {
    if (!off[1]) {
      if (c()) {
        if (millis() - t[1] >= timedelay[1]) {
          t[1] = millis();
            Serial.println("2o");
          Serial.flush();
          phplogging("2");
          off[1] = 1;
        }
      } else {
          Serial.println("2o");
          Serial.flush();
        phplogging("2");
        off[1] = 1;
      }
    }
  } else {
    t[1] = millis();
  }

}
void serialEvent() {
  while (Serial.available() > 0) {
    char inChar = (char)Serial.read(); // get the new byte:
    comString += inChar;               // add it to the comString:
    if (inChar == '\n') {
      comString.trim();
      if (comString[0] == '!' and (comString[1] & 0x0f) == 1)onmotor(0);
      if (comString[0] == 'c' and (comString[1] & 0x0f) == 1) offmotor(0);
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
  y++;
}
void offmotor(int i) {
  onswitch[i] = 0;
  y--;
  i += 1;
  phplogging("-" + (String)i);
}
unsigned long settimedelay() {
  return y * 10000;
}

bool c() {
  return y - 1 > 0;
}

void phplogging(String num) {
    if (!client.connect(host, 80)) {
//    Serial.println("connection failed");
      digitalWrite(16,LOW);
    return;
  } else {
    digitalWrite(16,HIGH);
//    Serial.println("--- connection success !!! ---");
  }
  Serial.println("num: "+num);
  String url = "/datalogger.php?case=" + num; //ชุด Directory ที่เก็บไฟล์ และตัวแปรที่ต้องการจะฝาก
  //ส่งค่าตัวแปร
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Connection: close\r\n\r\n");
               
}
