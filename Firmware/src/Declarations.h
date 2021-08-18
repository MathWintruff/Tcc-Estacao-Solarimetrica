#include <Arduino.h>
#include <ESP32Servo.h>

const int batVoltageSensor = 13;
const int servoPin = 25;
const int btn[2] = {27,14};

Servo myservo;

void InitializeComponents(){
    pinMode(btn[0], INPUT_PULLUP);
    pinMode(btn[1], INPUT_PULLUP);

    ESP32PWM::allocateTimer(0);
	ESP32PWM::allocateTimer(1);
	ESP32PWM::allocateTimer(2);
	ESP32PWM::allocateTimer(3);
	myservo.setPeriodHertz(50);    // standard 50 hz servo
	myservo.attach(servoPin, 680, 2260); // attaches the servo on pin 18 to the servo object
}