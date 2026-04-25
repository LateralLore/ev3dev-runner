#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <ctype.h>
#include <unistd.h>

#include "ev3.h"
#include "ev3_tacho.h"

#define MAXLINELEN 100

int getop(char *s); /* gets operation as integer, s is output string, uses getch */
void push(int d); /* pushes value onto stack */
int pop(void); /* pops value off of stack */

/* handles speeds and directions taken from stdin */
int handler(uint8_t *snm)
{
  char o[MAXLINELEN];
  uint8_t flags;
  int i;
  uint8_t snd[] = {*(snm+2),*(snm+1)};

  while ((i = getop(o)) != '\n') {
    switch (i) {
    case 1:
      push(atoi(o));
      break;
    case 's': /* set speed */
      switch (i = getop(o)) {
      case 'l': /* left motor */
	set_tacho_speed_sp(*(snm+2), pop());
	break;
      case 'r': /* right motor */
	set_tacho_speed_sp(*(snm+1), pop());
	break;
      case 'c': /* central motor */
	set_tacho_speed_sp(*snm, pop());
	break;
      default:
	printf("error: motor %c is not recognised\n", i);
	return -1;
      }
      break;
    case 'p': /* set position */
      switch (i = getop(o)) {
      case 'l':
	set_tacho_position_sp(*(snm+2), pop());
	break;
      case 'r':
	set_tacho_position_sp(*(snm+1), pop());
	break;
      case 'c':
	set_tacho_position_sp(*snm, pop());
	break;
      default:
	printf("error: motor %c is not recognised\n", i);
	return -1;
      }
      break;
    case 't': /* set time */
      switch (i = getop(o)) {
      case 'l':
	set_tacho_time_sp(*(snm+2), pop());
	break;
      case 'r':
	set_tacho_time_sp(*(snm+1), pop());
	break;
      case 'c':
	set_tacho_time_sp(*snm, pop());
	break;
      default:
	printf("error: motor %c is not recognised\n", i);
	return -1;
      }
      break;
    case 'd': /* set polarity of motors */
      switch (i = getop(o)) {
      case 'l':
	set_tacho_polarity_inx(*(snm+2), pop());
	break;
      case 'r':
	set_tacho_polarity_inx(*(snm+1), pop());
	break;
      case 'c':
	set_tacho_polarity_inx(*snm, pop());
	break;
      default:
	printf("error: motor %c is not recognised\n", i);
	return -1;
      }
      break;
    case 'r': /* give run command (must be given as number and not as string) */
      switch (i = getop(o)) {
      case 'l':
	set_tacho_command_inx(*(snm+2), pop());
	break;
      case 'r':
	set_tacho_command_inx(*(snm+1), pop());
	break;
      case 'c':
	set_tacho_command_inx(*snm, pop());
	break;
      case 'd': /* left and right motor, for driving */
	multi_set_tacho_command_inx(snd, pop());
	break;
      default:
	printf("error: motor %c is not recognised\n", i);
	return -1;
      }
      break;
    case 'f': /* special flags for complex handling, syntax must be done on multiple lines */
      switch (i = getop(o)) {
      case 'w':
	for (i = 0; i < 3; i++)
	  do {
	    get_tacho_state_flags(*(snm+i), &flags);
	  } while (flags > 0);
	break;
      case 's': /* sleeps for amount of us */
	usleep(pop());
	break;
      case 'r': /* pops and returns value from stack */
	return pop();
      case 'l': /* gives signal to start line follower */
	return 2;
      case 'e': /* returns end signal */
	return 0;
      default:
	printf("error: %c is not a recognised flag\n");
	return -1;
      }
      break;
    default:
      printf("error: %c is not recognised\n", i);
      return -1;
    }
  }
  return 1;
}

    
