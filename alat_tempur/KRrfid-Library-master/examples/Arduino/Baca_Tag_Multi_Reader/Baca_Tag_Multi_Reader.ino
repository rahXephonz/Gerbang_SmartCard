#define rst         9
#define sda1        10
#define sda2        8
#define jumlah_reader   2
byte sda_pin[] = {sda1, sda2};
#include<KRrfidMulti.h>

void setup() {
  Serial.begin(9600);
  rfidBegin();
}

void loop() {
  getTAG();
  if (TAG != "") {
    Serial.print(READER);
    Serial.print(":");
    Serial.println(TAG);
    TAG = "";
  }
}
