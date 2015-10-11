#include "mpl3115a2.hpp"

#include <Arduino.h>

#include <Wire.h>
#ifndef TwoWire_h
#error Need to #include <Wire.h>
#endif

#include <SparkFunMPL3115A2.h>
#ifndef MPL3115A2_ADDRESS
#error Need to #include <SparkFunMPL3115A2.h>
#endif

namespace
{
  MPL3115A2 pressureTemp;
  float elevation = -1;
  bool mpl3115a2Initialized = false;
}

void MPL3115A2Sensor::initialize(float elevationInMeters, ReadPeriod period)
{
  elevation = elevationInMeters;
  
  Wire.begin();
  
  pressureTemp.begin();
  pressureTemp.setModeBarometer();
  pressureTemp.setOversampleRate(period);
  pressureTemp.enableEventFlags();
  
  mpl3115a2Initialized = true;
}

float MPL3115A2Sensor::getPressurePa()
{
  float ret = -1;
  if (mpl3115a2Initialized)
  {
    ret = pressureTemp.readPressure();
  }
  return ret;
}

float MPL3115A2Sensor::getPressureHg()
{
  float ret = -1;
  if (mpl3115a2Initialized)
  {
    const float PASCALS_TO_MILLIBARS(0.01);
    float pressurePa = getPressurePa() * PASCALS_TO_MILLIBARS;
    
    // formula from:
    // https://learn.sparkfun.com/tutorials/mpl3115a2-pressure-sensor-hookup-guide
    //
    // Pressure (millibars) = A * (1 + B) ^ 5.255303
    //                        where A = pressurePa - 0.3,
    //                        B = 8.42288e-5 * elevation / (A ^ 0.190284)
    float A = pressurePa - 0.3;
    float B = 8.42288e-5 * elevation / pow(A, 0.190284);
    float millibars = A * pow((1 + B), 5.255303);
    
    const float MILLIBAR_TO_INCH_HG(0.02953);
    ret = millibars * MILLIBAR_TO_INCH_HG;
  }
  return ret;
}

float MPL3115A2Sensor::getTemperatureF()
{
  float ret = -1;
  if (mpl3115a2Initialized)
  {
    ret = pressureTemp.readTempF();
  }
  return ret;
}

float MPL3115A2Sensor::getTemperatureC()
{
  float ret = -1;
  if (mpl3115a2Initialized)
  {
    ret = pressureTemp.readTemp();
  }
  return ret;
}
