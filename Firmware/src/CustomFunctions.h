#include <Arduino.h>
#include <SPI.h>
#include <LoRa.h>

double GetAnalogVoltage(byte pin){
    double meassureBuffer = 0;
    for(int i=0; i<100; i++){
        double reading = analogRead(pin);
        meassureBuffer += (-0.000000000000016 * pow(reading,4) + 0.000000000118171 * pow(reading,3)- 0.000000301211691 * pow(reading,2)+ 0.001109019271794 * reading + 0.034143524634089);
        delay(1);
    }
    return meassureBuffer/100;
}

struct BatteryData{
    double Voltage;
    double Percentage;
};

BatteryData GetBatteryData(byte batterySensePin){
    BatteryData bat;
    double reading = GetAnalogVoltage(batterySensePin);

    double batVoltage = reading/0.228;
    bat.Voltage = batVoltage;

    double batPercentage = (reading-1.9152)/0.009576;
    bat.Percentage = (batPercentage <= 0) ? 0 : (batPercentage >= 100) ? 100 : batPercentage;

    return bat;
}

String BatVoltagePhrase(byte batPin){
  BatteryData bat = GetBatteryData(batPin);
  String finalPhrase = "The battery voltage is: ";
  finalPhrase.concat(bat.Percentage);
  finalPhrase.concat(" Percent, and the Voltage is: ");
  finalPhrase.concat(bat.Voltage);
  finalPhrase.concat("v.");
  return finalPhrase;
}

void LoraDump(){
     Serial.println("LoRa Dump Registers");
     LoRa.setPins(5, 15, 4);

  // override the default CS, reset, and IRQ pins (optional)
  // LoRa.setPins(7, 6, 1); // set CS, reset, IRQ pin

  if (!LoRa.begin(915E6)) {         // initialize ratio at 915 MHz
    Serial.println("LoRa init failed. Check your connections.");
    while (true);                   // if failed, do nothing
  }

  LoRa.dumpRegisters(Serial);
}