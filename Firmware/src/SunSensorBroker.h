#include <Arduino.h>
#include <ESP32Servo.h>

Servo myservo;

void InicializeSunSensor(){
    ESP32PWM::allocateTimer(0);
	ESP32PWM::allocateTimer(1);
	ESP32PWM::allocateTimer(2);
	ESP32PWM::allocateTimer(3);
	myservo.setPeriodHertz(50);    // standard 50 hz servo
	myservo.attach(servoMotorPin, 680, 2260); // attaches the servo on pin 18 to the servo object
}

double GetPanelCurrent(){
   double voltage = GetAnalogVoltage(panelVoltageSensor);
   double current = voltage/0.015;
   return current;
}

String PanelPhrase(byte panelSensePin){
  String finalPhrase = "The panel current is: ";
  finalPhrase.concat(GetPanelCurrent());
  finalPhrase.concat("mA.");
  return finalPhrase;
}

struct SunData {
    String angle = "-75|-70|-65|-60|-55|-50|-45|-40|-35|-30|-25|-20|-15|-10|-05|00|05|10|15|20|25|30|35|40|45|50|55|60|65|70|75";
    String current = "";
};

SunData lastSunInclinationReading;

void CheckSunInclination(){
    SunData sunData;
    int servoAngle = 25;
    int readingIndex = 0, angleReadigns[31];
    double currentReadings[31];

    myservo.write(25);
    delay(600);

    while(servoAngle <= 175){
        myservo.write(servoAngle);
        delay(200);
        currentReadings[readingIndex] = GetPanelCurrent();
        angleReadigns[readingIndex] = servoAngle;

        readingIndex++;
        servoAngle = servoAngle + 5;
        delay(10);
    }
    myservo.write(100);

    sunData.current = "";

    for(int readingCounter = 0; readingCounter <= 30; readingCounter++){
        if (readingCounter == 0){
          sunData.current.concat(currentReadings[readingCounter]);
        }else{
          sunData.current.concat("|");
          sunData.current.concat(currentReadings[readingCounter]);
        }
        delay(1);
    }
    lastSunInclinationReading.current = sunData.current;
}