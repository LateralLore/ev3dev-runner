#include <stdint.h>
#include "ev3.h"
#include "ev3_sensor.h"

/* grabs info from sensors, input is an array with the sensor sequence numbers */
float *grabber(uint8_t *sns, float *buf)
{
  int i;
  for (i = 0; i < 4; i++, sns++) {
    get_sensor_value0(*sns, buf++);
    get_sensor_value1(*sns, buf++);
    get_sensor_value2(*sns, buf++);
  }
  return buf;
}
