#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "list.h"
#include "error.h"



/*func*/
int list_create_new_node(List** head, char* name, int address, short attributes)
{
	symbol_node* temp;

	if (list_isEmpty)
	{
		*head = (symbol_node*)malloc(sizeof(symbol_node));
			if (!head)
				fatal_error(ErrorMemoryAlloc);
	}
	else
	{
		temp = (*head);
		while (temp->next) temp = temp->next; /* run to end of list */

		temp->next = (symbol_node*)malloc(sizeof(symbol_node));
		if (!(temp->next))
			fatal_error(ErrorMemoryAlloc);
		temp = temp->next;
	}
	/* insert data */
	temp->symbol_name = strcpy(temp->symbol_name, name);
	temp->symbol_address = address;
	temp->symbol_attributes = strcpy(temp->symbol_attributes, attributes);
	temp->next = NULL;
	
	return 1;
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



int list_isEmpty(const List* lst)
{
	return lst->head == NULL;
}


/*פונקציה לשיחרור רשימה בסוף שימוש.*/
void list_free_symbol_list(List* theList)
{
	symbol_node* current = theList->head;
	symbol_node* next;

	while (current)
	{
		next = current->next;
		free(current);
		current = next;
	}
}
