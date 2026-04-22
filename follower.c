#include <stdio.h>
#include <stdint.h>
#include "ev3_tacho.h"

int handler(uint8_t *snm);
float *grabber(uint8_t *sns);
int sorter(float *refp);

/* all of the motor speeds are given in the instructions */

/*follower: follows line, takes motor and sensor squence numbers as arguments */
int follower(uint8_t *snm, uint8_t *sns)
{
  int i;
  uint8_t snl = *(snm+2)
  uint8_t snr = *(snm+1);
  uint8_t snd[2] = {snl, snr};

  switch(sorter(grabber(sns))) {
  case 0:
    break;
  case 3: case 6: case 7: case 12: case 14: case 15:
    return handler(snm);
  case 1: case 2: /* line is to left of sensors */
    set_tacho_command_inx(snl, 6); /* stops left motor */
    set_tacho_command_inx(snr, 1); /* starts right motor */
    break;
  case 4: case 8: /* line is to right of sensors */
    set_tacho_command_inx(snl, 1);
    set_tacho_command_inx(snr, 6);
    break;
  case 5: case 9: case 10: case 11: case 13:
    /* ?, maybe call handler */
    break;
  default:
    printf("error: unkown value\n");
    return -1;
  }
  return 1;
}
