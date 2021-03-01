
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "error.h"



extern fp;

typedef struct symbol_node {

	void* symbol_name;
	int symbol_address;
	char* symbol_attributes;

	symbol_node next;

}symbol_node;


typedef struct symbol_list
{
	symbol_node* head;
}List;



/* dec*/
void list_free_symbol_list(List* theList);
int list_isEmpty(const List* lst);
int list_create_new_node(List** head, char* name, int address, short attributes);