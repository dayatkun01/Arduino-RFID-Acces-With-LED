#include <MFRC522.h>
#include <Arduino.h>
#include <SPI.h>

int RFIDsdaPin = 2, RFIDsckPin = 13, RFIDmosiPin = 11;
int RFIDmiPin = 12, RFIDrstPin = 3;MFRC522 RFIDrunner(RFIDsdaPin, RFIDrstPin);
int LEDredPin = 4;int LEDgreenPin = 5;int SesionMaxTimePerScan = 10;
unsigned long Cooldown1;

int LEDstate[2] = {1, 0};int RFIDstate[2] = {0, 0};

void LEDtoggle() {LEDstate[0] = (LEDstate[0] == 0 ? 1 : 0);LEDstate[1] = (LEDstate[1] == 0 ? 1 : 0);}
void LEDsetState(int redLight, int greenLight) {LEDstate[0] = redLight;LEDstate[1] = greenLight;}
void RFIDgrantAccess() {RFIDstate[0] = 1;RFIDstate[1] = SesionMaxTimePerScan;LEDsetState(0, 1);}
void RFIDungrantAccess() {RFIDstate[0] = 0;RFIDstate[1] = 0;LEDsetState(1, 0);}

void setup() {
  pinMode(LEDredPin, OUTPUT);pinMode(LEDgreenPin, OUTPUT);

  Serial.begin(250000);
  SPI.begin();
  RFIDrunner.PCD_Init();

  Serial.print("Started Listening....");

  LEDsetState(1, 0);
}

void loop() {
  Serial.println(String(LEDstate[0]) + " " + String(LEDstate[1]));
  digitalWrite(LEDredPin, (LEDstate[0] == 1 ? HIGH : LOW));digitalWrite(LEDgreenPin, (LEDstate[1] == 1 ? HIGH : LOW));
  if(RFIDstate[0] == 0) {
    if(!RFIDrunner.PICC_IsNewCardPresent()) {return;}
    if(!RFIDrunner.PICC_ReadCardSerial()) return;
    Serial.println();
    for (int i = 0; i < RFIDrunner.uid.size; i++) {
      Serial.print(RFIDrunner.uid.uidByte[i] < 0x10 ? " 0" : " ");
      Serial.print(RFIDrunner.uid.uidByte[i], HEX);
      RFIDgrantAccess();
    }
  } 
  else {
    if(RFIDstate[1] < 1){RFIDungrantAccess();}
    if(abs(millis() - Cooldown1 > 1000)) {Cooldown1 = millis();RFIDstate[1]--;}
  }
}