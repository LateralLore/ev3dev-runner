#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "ev3.h"
#include "ev3_port.h"
#include "ev3_sensor.h"
#include "ev3_tacho.h"

#include "handler.c"

/* init: properly initialises everything; snm and sns arrays are in format
   snm[0] = left motor
   snm[1] = right motor
   snm[2] = central motor

   sns[0-3] = sensors 1-4
*/

int init(uint8_t *snm, uint8_t *sns)
{
  int i = 0;
  
  if (ev3_init() < 1)
    printf("error: ev3_init fail\n"), i--;
  else
    printf("pass: ev3 init\n");
  if (ev3_port_init() < 8)
    printf("error: port init fail\n"), i--;
  else
    printf("pass: port init\n");
  if (ev3_tacho_init() < 3)
    printf("error: tacho init fail\n"), i--;
  else
    printf("pass: tacho init\n");
  if (ev3_sensor_init() < 4)
    printf("error: sensor init fail\n"), i--;
  else
    printf("pass: sensor init\n");
  if (i < 0)
    return -1;

  while ((i = handler(0)) > 0)
    *snm++ = ev3_search_port((uint8_t) i, 0);
  while ((i = handler(0)) > 0)
    *sns++ = ev3_search_port((uint8_t) i, 0);

  set_tacho_polarity_inx(snm[1], TACHO_INVERSED);

  multi_set_sensor_mode_inx(sns, LEGO_EV3_COLOR_RGB_RAW);

  return 1;
}

  
