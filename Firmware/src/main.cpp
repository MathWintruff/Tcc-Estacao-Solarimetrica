/*******************************************************************************
 * BSD 3-Clause License
 * 
 * Copyright (c) 2021, Otoma Systems
 * All rights reserved.
 *******************************************************************************/

#include <Arduino.h>
#include <Declarations.h>
#include <LoraBroker.h>
#include <CustomFunctions.h>
#include <ConnectionSetup.h>
String teste;
int pos = 0;
void setup() {
  Serial.begin(115200);
  LoraStart();
  delay(1000);

  InitializeComponents();
  WifiSetup();
  OtaSetup();
  //GetLoraInfoOnSerial();
}

void loop() {
  VerifyLoraCommand();
  LoraRead(false);
  WebControler();
  delay(1);

  
    if(digitalRead(btn) == 0){
    Serial.println(BatteryPhrase(batVoltageSensor));
    Serial.println(PanelPhrase(panelVoltageSensor));
    Serial.println(GetTemperature(thermistorSensor));
    //LoraSendMessage("95|13.2|32.5|45|200");
  }
  myservo.write(SwipeServo());
    delay(600);
}