#ifndef LIST_H_
#define LIST_H_

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "error.h"



typedef struct Lebel* Shead;
typedef struct Line* Lhead;

/* enum for Attributes field in the symbol table/list. */
typedef enum {

	codeType,
	dataType,
	externType,
	entryType

} Attributes;


/**
* Hold the 12 bits in bit field
*/
typedef struct {
	unsigned int source : 2;
	unsigned int target : 3;
	unsigned int func : 4;
	unsigned int opcode : 4;
} MachineCodeBit;


/**
* Union That hold the 12 bits.
* if its instruction so the bits hold together.
*/
typedef union {
	MachineCodeBit separateBits;
	unsigned long allBits;
} MachineCode;


/**
* node for the main table - node is a "line".
*/
typedef struct Line {
	char* lebel;
	int address;
	MachineCode bcode;
	int is_instruction;
	char are;
	struct Line* next;
}Line;

/**
*
*/
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
Line* newLineNode(Line* node, int line, int instruction, char ARE);
Lebel* NewLebelNode();

#endif