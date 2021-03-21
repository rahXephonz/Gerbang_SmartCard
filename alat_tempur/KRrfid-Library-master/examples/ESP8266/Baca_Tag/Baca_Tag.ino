byte sda = 0;
byte rst = 2;
#include<KRrfid.h>

void setup() {
  Serial.begin(9600);
  rfidBegin();
}

void loop() {
  getTAG();
  if (TAG != "") {
    Serial.print("TAG :");
    Serial.println(TAG);
    TAG = "";
  }
}
