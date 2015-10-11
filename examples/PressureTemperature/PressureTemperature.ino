#include <SparkFunMPL3115A2.h>
#include <Wire.h>
#include <mpl3115a2.hpp>

void setup()
{
  const float elevationInMeters(62.7);
  MPL3115A2Sensor::initialize(elevationInMeters);
  
  Serial.begin(9600);
}

void loop()
{
  Serial.print(MPL3115A2Sensor::getTemperatureF());
  Serial.println(" (F)");
  Serial.print(MPL3115A2Sensor::getPressureHg());
  Serial.println(" (inHg)");
}

