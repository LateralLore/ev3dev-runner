#include <stdio.h>
#include <ctype.h>

int getch(void);
void ungetch(int);

int getop(char *s)
{
  int c;
  
  while ((*s = c = getch()) == ' ' || c == '\t')
    ;
  *(s+1) = '\0';
  if (!isdigit(c) && c != '.' && c != '_')
    return c;
  if (c == '_')
    *s = '_';
  if (isdigit(c) || c == '_')
    while (isdigit(*++s = c = getch()))
      ;
  if (c == '.')
    while (isdigit(*++s = c = getch()))
      ;
  *s = '\0';
  if (c != EOF)
    ungetch(c);
  return 1;
}
  
