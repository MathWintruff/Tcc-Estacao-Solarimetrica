#include <Arduino.h>
#include <ESP32Servo.h>
#include <Declarations.h>
#include <CustomFunctions.h>
#include <SPI.h>
#include <LoRa.h>
#include <LoraTest.h>

int pos = 0;

void setup() {
  Serial.begin(115200);
  delay(1000);

  //LoraDump();

  InitializeComponents();
  SetupLoraLib();
}

void loop() {
  if(digitalRead(btn[0]) == 0){
    Serial.println(BatVoltagePhrase(batVoltageSensor));
    delay(200);
  }
  if(digitalRead(btn[1]) == 0){
    //myservo.write(0);
    delay(200);
  }
  os_runloop_once();
}