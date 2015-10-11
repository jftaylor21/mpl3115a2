#ifndef MPL3115A2_HPP
#define MPL3115A2_HPP

/**
 * Reads Barometric pressure and temperature from MPL3115A2
 * See http://cache.freescale.com/files/sensors/doc/data_sheet/MPL3115A2.pdf
 * Wraps https://github.com/sparkfun/MPL3115A2_Breakout
 */
namespace MPL3115A2Sensor
{
  /**
   * Choices for read period of the sensor.
   *
   * Long read periods are less noisy than short read periods.
   * Long read periods consume more energy than short read periods.
   * See datasheet for more details:
   * http://cache.freescale.com/files/sensors/doc/data_sheet/MPL3115A2.pdf
   */
  enum ReadPeriod
  {
    PERIOD_6_MSEC   = 0x000,
    PERIOD_10_MSEC  = 0x001,
    PERIOD_18_MSEC  = 0x010,
    PERIOD_34_MSEC  = 0x011,
    PERIOD_66_MSEC  = 0x100,
    PERIOD_130_MSEC = 0x101,
    PERIOD_258_MSEC = 0x110,
    PERIOD_512_MSEC = 0x111
  };
  
  /**
   * Initialize MPL3115A2 hardware.
   *
   * \param elevationInMeters Elevation of sensor.
   * \param ReadPeriod See comments about ReadPeriod enum.
   */
  void initialize(float elevationInMeters, ReadPeriod period=PERIOD_512_MSEC);
  
  /**
   * Reads barometric pressure in Pascals (Pa).
   *
   * \return Barometric pressure in Pascals (Pa).
   *         Returns -1, if uninitialized.
   */
  float getPressurePa();
  
  /**
   * Reads barometric pressure in inches Mercury (inHg).
   *
   * \return Barometric pressure in inches Mercury (inHg).
   *         Returns -1, if uninitialized.
   */
  float getPressureHg();
  
  /**
   * Reads temperature in Fahrenheight (F).
   *
   * \return Temperature in Fahrenheight (F).
   *         Returns -1, if uninitialized.
   */
  float getTemperatureF();
  
  /**
   * Reads temperature in Celcius (C).
   *
   * \return Temperature in Celcius (C).
   *         Returns -1, if uninitialized.
   */
  float getTemperatureC();
}

#endif