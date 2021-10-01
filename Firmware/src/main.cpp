/*******************************************************************************
 * BSD 3-Clause License
 * 
 * Copyright (c) 2021, Otoma Systems
 * All rights reserved.
 *******************************************************************************/

#include <Arduino.h>
#include <ESP32Servo.h>
#include <Declarations.h>
#include <CustomFunctions.h>
#include <LoraBroker.h>

int pos = 0;

void setup() {
  Serial.begin(115200);
  LoraStart();
  delay(1000);

  InitializeComponents();
  GetLoraInfo();
}

void loop() {
  VerifyLoraCommand();
  LoraRead();
    if(digitalRead(btn) == 0){
    Serial.println(BatteryPhrase(batVoltageSensor));
    Serial.println(PanelPhrase(panelVoltageSensor));
    Serial.println(GetTemperature(thermistorSensor));
    LoraSendMessage("95|13.2|32.5|45|200");
    static bool side = 0;
    side = !side;
    if (side){
      myservo.write(0);
    }else{
      myservo.write(180);
    }
    delay(200);
  }
}