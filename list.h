
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "error.h"
#include "asm.h"


extern fp;

/* enum for Attributes field in the symbol table/list. */
typedef enum{entryCode, entryData, code, data, external} Attributes;

typedef struct _node* node_pointer;

/* for symbol table - for define. */
typedef node_pointer symbolList;

/* for main table - for define. */
typedef node_pointer mainList;

/**
* abstruct node
*/
typedef struct _node {
	void* data;
	node_pointer next;
} List_node;


/**
* node for symbol table.
*/
typedef struct _symbol_line {
	char* symbol;
	int value; /* decimal */
	Attributes type;
}_symbol_line;

/**
* node for the main table - node is a "line".
*/
typedef struct _main_line {
	/*Lebel* lebel;*/
	int address;
	MachineCode bcode;
	char name;
	char are;
}_main_line;


/* */
node_pointer CreateAndaddToList(node_pointer head, void* data);
/* */
node_pointer createNewNode(void* data);
/* */
void freeList(node_pointer head, void(*_free_data)(void*));



