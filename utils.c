#include "utils.h"
#include <stdlib.h>

/* for symbol table - for define. */


/*
int IsBlank(char* c)
{
	if (((&c) == ' ') || ((&c) == '\t'))
		return 1;
	return 0;
}

char* NextWord(char* str)
{
  char *end;


  while(*str == ' ' || *str == '\t')
  {
	  str++;
  }

  if(*str == 0)
  {
	return str;
  }

  end = str + strlen(str) - 1;
  while(end > str && (*end == ' ' || *end == '\t'))
  {
	  end--;
  }


  end[1] = '\0';

  return str;
}*/

char* NextWord(char* x)
{
	while (IsBlank(*(x))) (x)++;
}