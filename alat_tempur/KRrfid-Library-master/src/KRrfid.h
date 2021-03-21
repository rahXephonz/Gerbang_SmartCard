#include <SPI.h>
#include <MFRC522.h>
MFRC522 mfrc522(sda, rst);
String TAG;

void getTAG()
{
    if (!mfrc522.PICC_IsNewCardPresent())
    {
        return;
    }
    if (!mfrc522.PICC_ReadCardSerial())
    {
        return;
    }
    String content = "";
    byte letter;
    for (byte i = 0; i < mfrc522.uid.size; i++)
    {
        content.concat(String(mfrc522.uid.uidByte[i]));
    }
    content.toUpperCase();
    if (content.substring(1))
    {
        TAG = String(content.substring(1));
    }
}

void rfidBegin()
{
    SPI.begin();
    mfrc522.PCD_Init();
}
