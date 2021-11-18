/*******************************************************************************
 * BSD 3-Clause License
 * 
 * Copyright (c) 2021, Otoma Systems
 * All rights reserved.
 *******************************************************************************/

#include <Arduino.h>
#include <Declarations.h>
#include <AdcBroker.h>
#include <CustomFunctions.h>
#include <TimerBroker.h>
#include <SunSensorBroker.h>
#include <ThermistorBroker.h>
#include <LoraBroker.h>
#include <ConnectionSetup.h>

void setup() {
  Serial.begin(115200);
  LoraStart();
  delay(1000);

  InitializeComponents();
  InicializeSunSensor();
  WifiSetup();
  OtaSetup();
  //GetLoraInfoOnSerial();
}

void loop() {
  VerifyLoraCommand();
  LoraRead(true);
  WebControler();
  if (CheckIfTimeHasPassed(2)) CheckIfSunIsPresentAndGetReading();
  delay(1);

  
    if(digitalRead(btn) == 0){
    CheckSunInclination();
  }
}