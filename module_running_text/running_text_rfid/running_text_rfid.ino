#include <Wire.h>
#include <LiquidCrystal_I2C.h>

byte sda = 10;
byte rst = 9;
#include <KRrfid.h>



LiquidCrystal_I2C lcd(0x27, 16, 2);


void setup() {

  Serial.begin(9600);
  rfidBegin();
  
  lcd.begin();
  lcd.setCursor(5,0);
  lcd.print("S");delay(200); lcd.print("E");delay(200);
  lcd.print("L");delay(200); lcd.print("A");delay(200);
  lcd.print("M");delay(200); lcd.print("A");delay(200);
  lcd.print("T");delay(200);

  lcd.setCursor(1,1);
  lcd.print("D");delay(200); lcd.print("A");delay(200);
  lcd.print("T");delay(200); lcd.print("A");delay(200);
  lcd.print("N");delay(200); lcd.print("G");delay(200);
  lcd.print(" T");delay(200); lcd.print("U");delay(200);
  lcd.print("A");delay(200); lcd.print("N");delay(200);
  lcd.print("!");delay(200); lcd.print("!");delay(200);
  lcd.print(":");delay(200); lcd.print(")");delay(3000);
  lcd.clear();
}

void loop() {

  int u;
  getTAG();
  if (TAG != "") {
    Serial.print("TAG :");
    Serial.println(TAG);
    TAG = "";
  }
  
  
  lcd.setCursor(0, 1);
  lcd.print("Silahkan Scan Kartu Anda Disini");
  lcd.setCursor(0, 0);
  lcd.print("Selamat Datang!! :)");
  for (u = 0 ; u < 16; u++) {
    lcd.scrollDisplayLeft();
    //lcd.scrollDisplayRight();
    delay(300);
  }
}
