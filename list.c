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

	newNode->data = NULL;;
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
node_pointer list_create_symbol_node(char* name,int address,short attributes)
{
	node_pointer newNode;

	newNode = (node_pointer)malloc(sizeof(symbol_node));
	if (!newNode)
		fatal_error(ErrorMemoryAlloc);
	newNode->symbol_name = name;
	newNode->symbol_address = address;
	newNode->symbol_attributes = attributes;
	
	return newNode;
}




List add_to_symbol_list(List list, char* name, int address, short attributes)
{
	node_pointer node, temp;

	node = list_create_symbol_node(name, address, attributes);

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


int list_search_symbol_list(node_pointer* List,const char* name)
{
	symbol_node* temp = List;

	while (temp)
	{
		if (strcmp(name, temp->symbol_name))
			return 1;
		temp = temp->next;
	}
}


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