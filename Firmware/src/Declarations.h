#include <Arduino.h>

const int batVoltageSensor = 39;    //VN
const int panelVoltageSensor = 36;  //VP
const int thermistorSensor = 34;
const int servoMotorPin = 33;
const int btn = 32;
const int resetPin = 23;

void InitializeComponents(){
    pinMode(btn, INPUT_PULLUP);
	
	pinMode(resetPin, OUTPUT);
	digitalWrite(resetPin, LOW);
}

void ResetEsp(){
	digitalWrite(resetPin, HIGH);
}