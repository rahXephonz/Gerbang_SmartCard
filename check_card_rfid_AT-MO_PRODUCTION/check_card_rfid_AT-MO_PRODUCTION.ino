#include <RFID.h>
#include <SPI.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

#define SS_PIN 10 //pin RFID yang bisa di ubah
#define RST_PIN 9 //pin RFID yang bisa di ubah
#define STEPPER_PIN_1 2
#define STEPPER_PIN_2 3
#define STEPPER_PIN_3 4
#define STEPPER_PIN_4 5

RFID rfid(SS_PIN,RST_PIN);

int serNum[5];

int card1[][5] = {
  {136,5,141,5,5} // DATA RIZKY
};

int card2[][5] = {
  {214,6,68,43,191} // DATA FAHRI
};

bool acces = false;

int step_number = 0;

void setup(){

    Serial.begin(9600);
    SPI.begin();
    rfid.init();
    lcd.begin();

    pinMode(STEPPER_PIN_1, OUTPUT);
    pinMode(STEPPER_PIN_2, OUTPUT);
    pinMode(STEPPER_PIN_3, OUTPUT);
    pinMode(STEPPER_PIN_4, OUTPUT);
    Serial.println("Silahkan Dekatkan Tag Kartu anda:");
    
}

void loop()
{
    lcd.setCursor(0, 1);
    lcd.print("Scan Kartu Anda!");
    lcd.setCursor(0, 0);
    lcd.print("Selamat Datang!! :)");

    /*
    int u;
    for (u = 0 ; u < 16; u++) 
    {
      lcd.scrollDisplayLeft();
      //lcd.scrollDisplayRight();
      delay(300);
    }*/

  if(rfid.isCard()){
    
    if(rfid.readCardSerial())
    {
       Serial.print(rfid.serNum[0]);
       Serial.print(" ");
       Serial.print(rfid.serNum[1]);
       Serial.print(" ");
       Serial.print(rfid.serNum[2]);
       Serial.print(" ");
       Serial.print(rfid.serNum[3]);
       Serial.print(" ");
       Serial.print(rfid.serNum[4]);
       Serial.print("");

       for(int x=0; x < sizeof (card1); x++)
       {
          for(int i=0; i < sizeof(rfid.serNum); i++)
          {
            if(rfid.serNum[i] != card1 [x] [i])
            {
              acces = false;
              break;  
            }
            
            else
            {
              acces = true;
            }
          }
       if(acces) break; // untuk card satu
       }

       for(int x=0; x < sizeof (card2); x++)
       {
          for(int i=0; i < sizeof(rfid.serNum); i++)
          {
            if(rfid.serNum[i] != card2 [x] [i])
            {
              acces = false;
              break;  
            }
            
            else
            {
              acces = true;
            }
          }
       if(acces) break; // untuk card satu
       }

if (acces){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Akses Diterima!");
    lcd.setCursor(0,1);
    lcd.print("And Welcome! :)");
    delay(2000);

    for(int a = 0; a < 2900; a++)
    {
      OneStep(true);
      delay(2);
    }
      delay(3000);
  
    for(int a = 0; a < 2900; a++)
    {
      OneStep(false);
      delay(2);
    }

}

else{
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Akses Ditolak!");
    lcd.setCursor(0,1);
    lcd.print("User Not Found!");
    delay(2000);
    lcd.clear();
}

}

rfid.halt();
}
}

void OneStep(bool dir){
  if(dir){
    switch(step_number){
    case 0:
    digitalWrite(STEPPER_PIN_1, HIGH);
    digitalWrite(STEPPER_PIN_2, LOW);
    digitalWrite(STEPPER_PIN_3, LOW);
    digitalWrite(STEPPER_PIN_4, LOW);
    break;
    case 1:
    digitalWrite(STEPPER_PIN_1, LOW);
    digitalWrite(STEPPER_PIN_2, HIGH);
    digitalWrite(STEPPER_PIN_3, LOW);
    digitalWrite(STEPPER_PIN_4, LOW);
    break;
    case 2:
    digitalWrite(STEPPER_PIN_1, LOW);
    digitalWrite(STEPPER_PIN_2, LOW);
    digitalWrite(STEPPER_PIN_3, HIGH);
    digitalWrite(STEPPER_PIN_4, LOW);
    break;
    case 3:
    digitalWrite(STEPPER_PIN_1, LOW);
    digitalWrite(STEPPER_PIN_2, LOW);
    digitalWrite(STEPPER_PIN_3, LOW);
    digitalWrite(STEPPER_PIN_4, HIGH);
    break;
  } 
    }
    
  else{
    switch(step_number){
    case 0:
    digitalWrite(STEPPER_PIN_1, LOW);
    digitalWrite(STEPPER_PIN_2, LOW);
    digitalWrite(STEPPER_PIN_3, LOW);
    digitalWrite(STEPPER_PIN_4, HIGH);
    break;
    case 1:
    digitalWrite(STEPPER_PIN_1, LOW);
    digitalWrite(STEPPER_PIN_2, LOW);
    digitalWrite(STEPPER_PIN_3, HIGH);
    digitalWrite(STEPPER_PIN_4, LOW);
    break;
    case 2:
    digitalWrite(STEPPER_PIN_1, LOW);
    digitalWrite(STEPPER_PIN_2, HIGH);
    digitalWrite(STEPPER_PIN_3, LOW);
    digitalWrite(STEPPER_PIN_4, LOW);
    break;
    case 3:
    digitalWrite(STEPPER_PIN_1, HIGH);
    digitalWrite(STEPPER_PIN_2, LOW);
    digitalWrite(STEPPER_PIN_3, LOW);
    digitalWrite(STEPPER_PIN_4, LOW);
} 
  }
step_number++;
  if(step_number > 4){
    step_number = 0;
  }
}
    
