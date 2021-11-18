#include <Arduino.h>
struct BatteryData{
    double voltage;
    double percentage;
};

BatteryData GetBatteryData(byte batterySensePin){
    BatteryData bat;
    double reading = GetAnalogVoltage(batterySensePin);

    double batVoltage = reading/0.231;
    bat.voltage = batVoltage;

    double batPercentage = (reading-1.9152)/0.009576;
    bat.percentage = (batPercentage <= 0) ? 0 : (batPercentage >= 100) ? 100 : batPercentage;

    return bat;
}

String BatteryPhrase(byte batterySensePin){
  BatteryData bat = GetBatteryData(batterySensePin);
  String finalPhrase = "The battery charge is: ";
  finalPhrase.concat(bat.percentage);
  finalPhrase.concat(" Percent, and the Voltage is: ");
  finalPhrase.concat(bat.voltage);
  finalPhrase.concat("v.");
  return finalPhrase;
}