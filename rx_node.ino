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
    Serial.begin(9600);  // Debugging only
    if (!driver.init())
         Serial.println("init failed");

    lcd.init();
}

void loop(){
    uint8_t buf[RH_ASK_MAX_MESSAGE_LEN];
    uint8_t buflen = sizeof(buf);

    if (driver.recv(buf, &buflen)) // Non-blocking
    {
      int i;

      // Message with a good checksum received, dump it.
      driver.printBuffer("Got:", buf, buflen);
      Serial.print("Buf[0] = ");
      Serial.println(buf[0]);
      Serial.println("=================");
      Serial.println((char)buf[0]);
      /*
      Serial.println((char)23);
      Serial.println((char)24);
      Serial.println((char)25);
      Serial.println((char)30);
      */
      Serial.println(buf[0],DEC);
      Serial.println(buf[0],HEX);
      Serial.println(buf[0],BIN);
      // Use this in case hex values are displayed
      //Serial.print("Received:");
      //for (i = 0; i < buflen; i++) Serial.print(buf[i]);
      //Serial.println("");


      lcd.backlight();
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("TMP: ");
      lcd.setCursor(4,0);
      lcd.print(buf[0]);

      lcd.setCursor(0,1);
      lcd.print("HDT: ");
      lcd.setCursor(4,1);
      lcd.print(buf[1]);
      //for (i = 0; i < buflen; i++) lcd.print(buf[i]);
    }
}
