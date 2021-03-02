#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "list.h"
#include "error.h"



/*func*/
node_pointer list_create_node(char* name,int address,short attributes)
{
	node_pointer newNode;

	newNode = (node_pointer)malloc(sizeof(symbol_node));
	if (!newNode)
		fatal_error(ErrorMemoryAlloc);
	newNode->symbol_name = name;
	newNode->symbol_address = address;
	newNode->symbol_attributes = attributes;
}




List list_add_to_list(List list, char* name, int address, short attributes)
{
	node_pointer node, temp;

	node = _list_create_node(name, address, attributes);

	temp = list;
	if (!list)
		list = node;
	else
	{
		while (temp->next)
			temp = temp->next;

		temp->next = node;
	}
}

/*
* פונקציה שבודקת האם סמל כבר קיים , אם כן אז מחזירה 1
* לעבוד על עניין ההחזרה
*/
int list_search_symbol(List* head,const char* name)
{
	symbol_node* temp = head;

	while (temp)
	{
		if (strcmp(name, temp->symbol_name))
			return 1;
		temp = temp->next;
	}
}



/*פונקציה לשיחרור רשימה בסוף שימוש.*/
void list_free_symbol_list(List List)
{
	symbol_node* curr = List;
	node_pointer* temp;

	while (curr)
	{
		temp = curr;
		curr = curr->next;
		free(temp);
	}
	return;
}