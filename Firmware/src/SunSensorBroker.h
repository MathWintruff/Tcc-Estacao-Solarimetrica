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
    String angle = "|-60|-45|-30|-15|0|15|30|45|60";
    String current = "";
};

SunData lastSunInclinationReading;

void CheckSunInclination(){
    SunData sunData;
    int servoAngle = 40;
    int readingIndex = 0;
    double currentReadings[9];

    myservo.write(40);
    delay(600);

    while(servoAngle <= 160){
        myservo.write(servoAngle);
        delay(200);
        currentReadings[readingIndex] = GetPanelCurrent();

        readingIndex++;
        servoAngle = servoAngle + 15;
        delay(10);
    }
    myservo.write(100);

    sunData.current = "";

    for(int readingCounter = 0; readingCounter <= 8; readingCounter++){
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