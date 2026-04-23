/*
 * WRO robot main.c
 */

/* standard library inclusions */
#include <stdio.h>
#include <stdint.h>
#include <string.h>

/* ev3dev-c inclusions */
#include "ev3.h"
#include "ev3_port.h"
#include "ev3_sensors.h"
#include "ev3_tachos.h"

int init(uint8_t *snm, uint8_t *snm); /* full init, returns 1 if successful, negative if fail */
int handler(uint8_t *snm); /* instruction handler */

int main(void)
{
  int hr;
  uint8_t snm[3], sns[4];

  if (init(snm, sns) < 1) {
    printf("error: main init fail, aborting program\n");
    return -1;
  }
  /* main routine, will take from handler unless specified otherwise in instructions */
  while ((hr = handler(snm)) > 0) {
    if (hr == 2)
      while (follower(snm) > 0)
	;
  }
  ev3_uninit();
  return 0;	
}
