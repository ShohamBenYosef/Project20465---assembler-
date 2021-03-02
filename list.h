
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "error.h"



extern fp;

/* List node pointer. */
typedef struct _node* node_pointer;

/*טבלת סמלים*/
typedef struct _node {
	void* symbol_name;
	int symbol_address;
	short symbol_attributes;

	node_pointer next;
} symbol_node; 



typedef node_pointer List;


/* dec*/
void list_free_symbol_list(List* theList);
int list_isEmpty(const List* lst);
int list_create_new_node(List** head, char* name, int address, short attributes);