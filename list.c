#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "list.h"
#include "error.h"



/*func*/
/*

לבנות פונקציה שתיצור צמתים ל2 הרשימות!
לבנות פונ' שתמחק את כל הצמתים מ2 הרשימות
לבנות פונק שתבדוק האם התוית כבר קיימת

*/


node_pointer CreateAndaddToList(node_pointer head, node_pointer node)
{
	node_pointer temp;

	node = createNewNode();


	temp = head;
	if (!head)
		head = node;
	else
	{
		while (temp->next)
			temp = temp->next;

		temp->next = node;
	}
	return head; /* returning pointer to the top of the list*/
}

node_pointer createNewNode()
{
	node_pointer newNode;

	newNode = (node_pointer)malloc(sizeof(node_pointer));
	if (!newNode)
		fatal_error(ErrorMemoryAlloc);

	newNode->data = NULL;
	newNode->next = NULL;

	return newNode;
}


void freeList(node_pointer head, void(*_free_data)(void*))
{
	node_pointer p = head, temp;

	while (p)
	{
		temp = p;
		p = p->next;

		/* to fix it and change name of var. */
		_free_data(temp->data);
		/*temp->data = NULL;
		temp->next = NULL;*/
		free(temp);
	}
}

/*
void list_free_symbol_list(node_pointer List)
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
}*/

void* search_in_list(node_pointer list, void* data, int(*_copmare)(void*, void*))
{
	node_pointer temp = list;

	while (temp)
	{
		if (!_copmare(data, temp->data))
			return temp->data;
	
		temp = temp->next;
	}
	return NULL;
}