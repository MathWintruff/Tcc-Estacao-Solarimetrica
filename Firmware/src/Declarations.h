#include <Arduino.h>
#include <ESP32Servo.h>

const int batVoltageSensor = 39;    //VN
const int panelVoltageSensor = 36;  //VP
const int thermistorSensor = 34;
const int servoMotorPin = 33;
const int btn = 32;
const int resetPin = 23;

Servo myservo;

void InitializeComponents(){
    pinMode(btn, INPUT_PULLUP);
	
	pinMode(resetPin, OUTPUT);
	digitalWrite(resetPin, LOW);

    ESP32PWM::allocateTimer(0);
	ESP32PWM::allocateTimer(1);
	ESP32PWM::allocateTimer(2);
	ESP32PWM::allocateTimer(3);
	myservo.setPeriodHertz(50);    // standard 50 hz servo
	myservo.attach(servoMotorPin, 680, 2260); // attaches the servo on pin 18 to the servo object
}

void ResetEsp(){
	digitalWrite(resetPin, HIGH);
}