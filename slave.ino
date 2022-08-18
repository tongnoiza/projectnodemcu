
int sensitive = 66; // สำหรับ 30A
int offset = 4100; // ค่าเริ่มต้น 2500 ปรับค่าตรงนี้เพื่อให้ค่ายังไม่มีโหลดเป็น 0.00
double v;
bool s = false;
String comString="";
void setup() {
  comString.reserve(128);
  Serial.begin(9600);
  pinMode(5, INPUT_PULLUP);
  pinMode(4,OUTPUT);
    pinMode(3,OUTPUT);
}

void loop() {
    while (Serial.available()) {
    if (Serial.available() > 0) {
      serialEvent();
      break;
    }
  }
  if (!digitalRead(5)) {
    if (!s) {
      s = true;
      Serial.println("!1");
      digitalWrite(4,HIGH);
    }
    else {
      s = false;
      Serial.println("c1");
       digitalWrite(4,LOW);
       digitalWrite(3,LOW);
    }
    Serial.flush();
    delay(300);
  }
  
//  double c = getCA();
//  if (c > 0.00 && s) {
//    Serial.println("e1");
//    s = false;
//  }
}

void serialEvent() {
  while (Serial.available() > 0) {
    char inChar = (char)Serial.read(); // get the new byte:
    comString += inChar;               // add it to the comString:
    if (inChar == '\n') {
      comString.trim();
      if (comString[0] == '1' and comString[1]=='o' )digitalWrite(3,HIGH);
      comString = "";
    }
  }
}
// หาค่ากระแสเฉลี่ย
double getCA() {
  int count = 200;
  double sum = 0;
  for (int i = 0; i < count; i++) {
    sum += getC();
  }
  double val = sum / count;
  return val;
}
// อ่านค่ากระแส
double getC() {
  int a = analogRead(A0);
  v = (a / 1024.0) * 5000;
  return  (v - offset) / sensitive;
}
