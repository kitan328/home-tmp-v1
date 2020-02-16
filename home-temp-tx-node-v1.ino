#include "LowPower.h"

#include <RH_ASK.h>
#include <SPI.h> // Not actually used but needed to compile
#include <dht.h>

#define DHT11_PIN 5

dht DHT;

RH_ASK driver;
// RH_ASK driver(2000, 2, 4, 5); // ESP8266: do not use pin 11

const unsigned int unitID = 1;

int lastTMP = 0, lastHDT = 0, nowTMP = 0, nowHDT = 0;

void setup(){
  driver.init();
}

void loop(){
  // READ DATA
  int chk = DHT.read11(DHT11_PIN);
  nowHDT = (int)DHT.humidity;
  nowTMP = (int)DHT.temperature;
  
  // check for anythings change?  
  if (lastTMP != nowTMP || lastHDT != nowHDT) {
    uint8_t msg[3] = {nowTMP, nowHDT, unitID};
    driver.send(msg, 3);
    driver.waitPacketSent();
  }  
  
  lastTMP = nowTMP;
  lastHDT = nowHDT;

  LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF); 
}
