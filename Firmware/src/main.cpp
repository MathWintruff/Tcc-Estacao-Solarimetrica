#include <Arduino.h>
#include <ESP32Servo.h>
const int batVoltageSensor = 13;
const int servoPin = 25;
const int btn[2] = {27,14};

Servo myservo;

int pos = 0;


int BatVoltageMeassure(){
  int meassureBuffer = 0;
  for(int i=0; i<100; i++){
    int batVoltage = analogRead(batVoltageSensor);
    meassureBuffer += batVoltage;
    delay(10);
  }
  int meassureMapped = map(meassureBuffer/100, 2356, 3550, 0, 100);
  return (meassureMapped <= 0) ? 0 : (meassureMapped >= 100) ? 100 : meassureMapped;
}

String BatVoltagePhrase(){
  int batPercent = BatVoltageMeassure();
  double batVoltage = (batPercent*0.042 + 8.4);
  String finalPhrase = "The battery voltage is: ";
  finalPhrase.concat(batPercent);
  finalPhrase.concat(" Percent, and the Voltage is: ");
  finalPhrase.concat(batVoltage);
  finalPhrase.concat("v.");
  return finalPhrase;
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  pinMode(btn[0], INPUT_PULLUP);
  pinMode(btn[1], INPUT_PULLUP);

  ESP32PWM::allocateTimer(0);
	ESP32PWM::allocateTimer(1);
	ESP32PWM::allocateTimer(2);
	ESP32PWM::allocateTimer(3);
	myservo.setPeriodHertz(50);    // standard 50 hz servo
	myservo.attach(servoPin, 680, 2260); // attaches the servo on pin 18 to the servo object
}

void loop() {
  Serial.println(BatVoltagePhrase());
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