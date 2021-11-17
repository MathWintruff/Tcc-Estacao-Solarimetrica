#include <Arduino.h>

double GetTemperatureByVoltage(byte thermistorPin){
  double R1 = 10000.0;   
  double Beta = 3950.0;  
  double To = 298.15;  
  double Ro = 10000.0;   
  double Vs = 3.3;
  double Vout, Rt = 0;
  double T, Tc = 0;

  Vout = GetAnalogVoltage(thermistorPin);

  Rt = R1 * Vout / (Vs - Vout);
  T = 1/(1/To + log(Rt/Ro)/Beta);  
  Tc = T - 273.15;                      
  return  Tc;
}