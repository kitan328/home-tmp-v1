/*
 RF433Mhz Receiver Code
 https://circuits4you.com
 Receiver is connected on PIN 11

 Arduino                     Receiver
  GND--------------------------GND
  D11--------------------------Data
  5V---------------------------VCC
*/

#include <RH_ASK.h>
#include <SPI.h> // Not actualy used but needed to compile

#include <LiquidCrystal_I2C.h>
// set the LCD address to 0x3F for a 16 chars and 2 line display
// Try to SCAN I2C First by
// Example -> Wire -> i2c_scanner
LiquidCrystal_I2C lcd(0x3F,20,4);  

RH_ASK driver;
// RH_ASK driver(2000, 2, 4, 5); // ESP8266: do not use pin 11

void setup(){


  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0,0);
  if (!driver.init()) {
     lcd.print("init failed");
     delay(5000);
  }
  lcd.print("T: ");
  lcd.setCursor(0,1);
  lcd.print("H: ");
}

void loop(){
    uint8_t buf[RH_ASK_MAX_MESSAGE_LEN];
    uint8_t buflen = sizeof(buf);

    if (driver.recv(buf, &buflen)) // Non-blocking
    {
      switch (buf[2]) {
        case 1:
          lcd.setCursor(3,0);
          lcd.print(buf[0]);
          
          lcd.setCursor(3,1);
          lcd.print(buf[1]);
          break;
        case 2:
          lcd.setCursor(6,0);
          lcd.print(buf[0]);
          
          lcd.setCursor(6,1);
          lcd.print(buf[1]);         
          break;
        case 3:
          lcd.setCursor(9,0);
          lcd.print(buf[0]);
          
          lcd.setCursor(9,1);
          lcd.print(buf[1]);
          break;
      }

    }
}
