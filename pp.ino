#include <WiFiManager.h>
const char* host = "tongza.000webhostapp.com";
#define pullup INPUT_PULLUP
bool onswitch[5], off[5];
bool on[5];
unsigned long returntime();
unsigned long timedelay[5];
void pressedbutton();
static int motorstart;
bool c();
unsigned long t[5];
void setup() {
  Serial.begin(9600);
  WiFi.mode(WIFI_STA); // explicitly set mode, esp defaults to STA+AP
  WiFiManager wm;
  bool res;
  // res = wm.autoConnect(); // auto generated AP name from chipid
  res = wm.autoConnect("testing"); // anonymous ap
  // res = wm.autoConnect("AutoConnectAP", "password"); // password protected ap
  // ESP.restart();
  if (!res)  Serial.println("Failed to connect");
  else  Serial.println("connected...yeey :)");

  pinMode(5, pullup);
  pinMode(4, pullup);
  motorstart = -1;

}

void loop() {
  if (!digitalRead(5)) {
    Serial.println("pressed botton 5 ");
    delay(300);
    pressedbutton(0);
  }
  if (!digitalRead(4)) {
    Serial.println("pressed button 16");
    delay(300);
    pressedbutton(1);
  }


  if (onswitch[0]) {
    if (off[0]) {

      if (c()) {
        timedelay[0] = returntime();
        if (millis() - t[0] >= timedelay[0]) {
          t[0] = millis();
          onswitch[0] = 0;
          motorstart++;
         
          !off[0];
          Serial.println("เครื่อง1 " + String(timedelay[0]));
        }
      } else {
        Serial.println("เครื่อง1 no delay");
        motorstart++;
        onswitch[0] = 0;
        !off[0];
      }
    }



  } else {
    t[0] = millis();
  }

  if (onswitch[1]) {
    if (!off[1]) {
      if (c()) {
        timedelay[1] = returntime();
        if (millis() - t[1] >= timedelay[1]) {
          Serial.println("เครื่อง 2 " + String(timedelay[1]));
          t[1] = millis();
          off[1] = 0;
          onswitch[1] = 0;
          motorstart++;
        }
      } else {
        Serial.println("เครื่อง 2 no delay");
        motorstart++;
        onswitch[1] = 0;
        off[1] = 0;
      }
    }

  } else {
    t[1] = millis();
  }

  if (onswitch[2]) {
    if (c()) {
      timedelay[2] = returntime();
      if (millis() - t[2] >= timedelay[2]) {
        t[2] = millis();
        onswitch[2] = 0;
        motorstart++;
      }
    } else {
      motorstart++;
      onswitch[2] = 0;
    }
  } else {
    t[2] = millis();
  }

  if (onswitch[3]) {
    if (c()) {
      timedelay[3] = returntime();
      if (millis() - t[3] >= timedelay[3]) {
        t[3] = millis();
        onswitch[3] = 0;
        motorstart++;
      }
    } else {
      onswitch[3] = 0;
    }
  } else {
    t[3] = millis();
  }

  if (onswitch[4]) {
    if (c()) {
      timedelay[4] = returntime();
      if (millis() - t[4] >= timedelay[4]) {
        t[4] = millis();
        onswitch[4] = 0;
        motorstart++;
      }
    } else {
      onswitch[4] = 0;
    }
  } else {
    t[4] = millis();
  }
}

void pressedbutton(int moter) {
  if (!onswitch[moter]) {
    off[moter] = 1;
    onswitch[moter] = 1;
  } else {
    motorstart--;
    onswitch[moter] = 0;
  }
}

unsigned long returntime() {
  return motorstart * 3000;
}

bool c() {
  return motorstart > 0;
}
