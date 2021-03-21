#include <SPI.h>
#include <MFRC522.h>
MFRC522 mfrc522[jumlah_reader];
String TAG;
int READER;

void dump_byte_array(byte *buffer, byte bufferSize) {
  String content = "";
  byte letter;
  for (byte i = 0; i < bufferSize; i++) {
    //    Serial.print(buffer[i] < 0x10 ? "0" : "");
    //    Serial.print(buffer[i]);
    content.concat(String(buffer[i]));
  }
  content.toUpperCase();
  if (content.substring(1))
  {
    TAG = String(content.substring(1));
  }
}

void rfidBegin() {
  SPI.begin();
  for (uint8_t reader = 0; reader < jumlah_reader; reader++) {
    mfrc522[reader].PCD_Init(sda_pin[reader], rst);
    Serial.print(F("Reader "));
    Serial.print(reader);
    Serial.print(F(": "));
    mfrc522[reader].PCD_DumpVersionToSerial();
  }
}

void getTAG() {
  for (uint8_t reader = 0; reader < jumlah_reader; reader++) {
    if (mfrc522[reader].PICC_IsNewCardPresent() && mfrc522[reader].PICC_ReadCardSerial()) {
      READER = reader;
      //      Serial.print(READER);
      //      Serial.print(": ");
      dump_byte_array(mfrc522[reader].uid.uidByte, mfrc522[reader].uid.size);
      //      Serial.println(TAG);
    }
  }
}