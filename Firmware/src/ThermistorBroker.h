#include <Arduino.h>

double GetTemperatureByVoltage(){
  const double beta = 3600.0;
  const double thermistorResistence = 10000.0;
  const double temperature = 273.0 + 25.0;
  const double rx = thermistorResistence * exp(-beta/temperature);

  // Parâmetros do circuito
  const double vcc = 3.3;
  const double resistor = 12000.0;

  double v = GetAnalogVoltage(thermistorSensor);;
  double rt = (vcc*resistor)/v - resistor;

  // Calcula a temperatura
  double t = beta / log(rt/rx);                   
  return  (t-273.0);
}