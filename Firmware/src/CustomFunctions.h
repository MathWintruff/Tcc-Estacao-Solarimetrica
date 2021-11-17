#include <Arduino.h>
#include <AdcBroker.h>
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

struct PanelData{
  double voltage;
  double current;
  double percentage;
};

PanelData GetPanelData(byte panelSensePin){
  PanelData panel; 
   panel.voltage = GetAnalogVoltage(panelSensePin);
   panel.current = panel.voltage/0.015;
   panel.percentage = 220/panel.current;
   return panel;
}

String PanelPhrase(byte panelSensePin){
  PanelData panel = GetPanelData(panelSensePin);
  String finalPhrase = "The panel voltage is: ";
  finalPhrase.concat(panel.voltage);
  finalPhrase.concat("v, the current is: ");
  finalPhrase.concat(panel.current);
  finalPhrase.concat("mA and the power percentage is: ");
  finalPhrase.concat(panel.percentage);
  finalPhrase.concat("%.");
  return finalPhrase;
}

double GetTemperature(byte temperatureSensorPin){
  double voltage = GetAnalogVoltage(temperatureSensorPin);
  return voltage;
}

int SwipeServo(){
  static boolean side = false;
  static int angle = 30;
  switch (side)
  {
  case false:
    if(angle<175){
      angle = angle+5;
    }else{
      side = true;
    }
    break;

  case true:
    if(angle>30){
      angle = angle-5;
    }else{
      side = false;
    }
    break;
  }
  return angle;
}