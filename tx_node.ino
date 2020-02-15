/*
433MHz Transmitter Code
https://circuits4you.com
Transmitter is connected on PIN 12

 Arduino                     Transmitter
  GND--------------------------GND
  D12--------------------------Data
  5V---------------------------VCC

*/
#include "LowPower.h"

#include <RH_ASK.h>
#include <SPI.h> // Not actually used but needed to compile
#include <dht.h>

#define DHT11_PIN 5

dht DHT;

RH_ASK driver;
// RH_ASK driver(2000, 2, 4, 5); // ESP8266: do not use pin 11

int lastTMP = 0, lastHDT = 0, nowTMP = 0, nowHDT = 0;

void setup(){
    Serial.begin(9600);    // Debugging only
    if (!driver.init())
         Serial.println("init failed");
}

void loop(){
  // READ DATA
  //Serial.print("DHT11, \t");
  int chk = DHT.read11(DHT11_PIN);
  /*
  switch (chk)
  {
    case DHTLIB_OK:  
    Serial.print("OK,\t"); 
    break;
    case DHTLIB_ERROR_CHECKSUM: 
    Serial.print("Checksum error,\t"); 
    break;
    case DHTLIB_ERROR_TIMEOUT: 
    Serial.print("Time out error,\t"); 
    break;
    case DHTLIB_ERROR_CONNECT:
        Serial.print("Connect error,\t");
        break;
    case DHTLIB_ERROR_ACK_L:
        Serial.print("Ack Low error,\t");
        break;
    case DHTLIB_ERROR_ACK_H:
        Serial.print("Ack High error,\t");
        break;
    default: 
    Serial.print("Unknown error,\t"); 
    break;
  }
  */
  nowHDT = (int)DHT.humidity;
  nowTMP = (int)DHT.temperature;

  // check for anythings change?  
  if (lastTMP != nowTMP || lastHDT != nowHDT) {
    Serial.println("Sensor(s) sens a change");  
    Serial.print("Temperature = ");
    Serial.println(nowTMP);
    
    Serial.print("Humidity = ");
    Serial.println(nowHDT);
    Serial.println("========================================");

    
    //uint8_t msg[3] = {(int)DHT.temperature, (int)DHT.humidity, 22};
    uint8_t msg[3] = {nowTMP, nowHDT, 22};
    driver.send(msg, 3);
    driver.waitPacketSent();
  }
  
  //delay(200);
  
  lastTMP = nowTMP;
  lastHDT = nowHDT;

  LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF); 
  //goToSleep();
  //LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
}
