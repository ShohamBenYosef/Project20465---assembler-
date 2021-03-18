#include "utils.h"
#include <stdlib.h>

/* for symbol table - for define. */
typedef struct LebelList
{
	struct Lebel* lebel_list_head;
}LebelList;

/* for main table - for define. */
typedef struct MainList
{
	struct Line* main_list_head;
}MainList;



int IsBlank(char* c)
{
	if (((c) == ' ') || ((c) == '\t'))
		return 1;
	return 0;
}

char* NextWord(char* x)
{
	while (IsBlank(x))
		(x)++;
	return x;
}