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
    int angle = 0;
    int current = 0;
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

    int bestReading = 0;

    for(int readingCounter = 0; readingCounter <= 30; readingCounter++){
        if(currentReadings[readingCounter] >= currentReadings[bestReading]){
            bestReading = readingCounter;
        }
        delay(1);
    }

    sunData.angle = (angleReadigns[bestReading])-100;
    sunData.current = currentReadings[bestReading];

    if(sunData.current >= 1) lastSunInclinationReading = sunData;
}

bool CheckIfSunIsPresentAndGetReading(){
    double readingsSum = 0;
    myservo.write(155);
    delay(500);
    readingsSum = GetPanelCurrent();
    myservo.write(45);
    delay(500);
    readingsSum += GetPanelCurrent();
    myservo.write(100);
    delay(500);
    readingsSum += GetPanelCurrent();

    if(readingsSum >= 10) {
      CheckSunInclination();
      return true;
    }else return false;
}


int SwipeServo(){
  static boolean side = false;
  static int angle = 30;
  if(side){
    if(angle>30){
      angle = angle-5;
    }else{
      side = false;
    }
  }else{
    if(angle<175){
      angle = angle+5;
    }else{
      side = true;
    }
  return angle;
  }
}