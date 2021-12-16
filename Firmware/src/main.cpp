/*******************************************************************************
 * BSD 3-Clause License
 * 
 * Copyright (c) 2021, Otoma Systems
 * All rights reserved.
 *******************************************************************************/

#include <Arduino.h>
#include <Declarations.h>
#include <AdcBroker.h>
#include <BatteryBroker.h>
#include <TimerBroker.h>
#include <SunSensorBroker.h>
#include <ThermistorBroker.h>
#include <LoraBroker.h>
#include <ConnectionSetup.h>

void setup() {
  Serial.begin(115200);
  LoraStart();
  delay(2000);

  InitializeComponents();
  InicializeSunSensor();
  WifiSetup();
  OtaSetup();
}

void loop() {
  VerifyLoraCommand();
  LoraRead(true);
  WebControler();
  if (CheckIfTimeHasPassed(2)) {
    GetInfoAndSendWithLora();
  }

  delay(10);
  
    if(digitalRead(btn) == 0){
      JoinNetwork();
      GetInfoAndSendWithLora();
  }
}