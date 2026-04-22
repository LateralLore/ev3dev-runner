#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "ev3.h"
#include "ev3_port.h"
#include "ev3_sensor.h"
#include "ev3_tacho.h"

int init(uint8_t *snm, uint8_t *sns)
{
  int i = 0;
  uint8_t j, k;
  
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
  for (i = 0, k = 0; i < 4; i++, k++) {
    ev3_search_sensor(LEGO_EV3_COLOR, &j, k);
    k = j;
    *(sns + (ev3_sensor_desc_port(j)-49)) = j;
  }
  for (i = 0, k = 0; i < 4; i++, k++) {
    ev3_search_tacho(LEGO_EV3_COLOR, &j, k);
    k = j;
    *(snm + (ev3_tacho_desc_port(j)-49)) = j;
  }
  set_tacho_polarity_inx(*(snm+1), TACHO_INVERSED);
  multi_set_sensor_mode_inx(sns, LEGO_EV3_COLOR_RGB_RAW);
  return 1;
}

  
