
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "error.h"



extern fp;

/* enum for Attributes field in the symbol table/list. */
typedef enum{codeType, dataType, externType ,entryType } Attributes;

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


/**
* node for the main table - node is a "line".
*/
typedef struct {
	char* lebel;
	int address;
	MachineCode* bcode;
	int is_instruction;
	char are;
	struct Line* next;
}Line;


typedef struct {
	char* lebel;
	int line; /* decimal*/
	Attributes type;
	struct Lebel* next;
}Lebel;





Line* addToMainList(Line* main_list_head, Line* new_node);
Lebel* addToSymbolList(Lebel* lebel_list_head, Lebel* new_node);
void freeLebelList(Lebel* head);
void freeLineList(Line* head);
Lebel* searchInLebelList(Lebel* head, char* lebel);
Line* searchInMainList(Line* head, char* lebel);