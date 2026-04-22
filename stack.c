#include <stdio.h>

#define MAXVAL 100

static int sp = 0;
static int val[MAXVAL];

void push(int i)
{
  if (sp < MAXVAL)
    val[sp++] = i;
  else
    printf("error: stack full, can't push %d\n", i);
}

int pop(void)
{
  if (sp > 0)
    return val[--sp];
  else {
    printf("error: stack empty\n");
    return 0.0;
  }
}
	   
