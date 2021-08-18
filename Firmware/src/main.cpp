#include <Arduino.h>
#include <ESP32Servo.h>
#include <Declarations.h>
#include <CustomFunctions.h>

int pos = 0;

void setup() {
  Serial.begin(115200);
  delay(1000);

  InitializeComponents();
}

void loop() {
  Serial.println(BatVoltagePhrase(batVoltageSensor));
  Serial.println(GetAnalogVoltage(batVoltageSensor));
  delay(500);

  if(digitalRead(btn[0]) == 0){
    myservo.write(180);
    delay(200);
  }
  if(digitalRead(btn[1]) == 0){
    myservo.write(0);
    delay(200);
  }
}