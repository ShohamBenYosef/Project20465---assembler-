#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "list.h"
#include "error.h"
#include "utils.h"

/**
* Add Node to the Lists
*/

Line* addToMainList(Line* list, Line* new_node)
{
	Line* p;

	p = list;
	if (!list)
	{
		list = new_node;
	}
	else
	{
		while (p)
		{
			p = p->next;
		}
		p = new_node;
	}

	return list; /* Returning pointer to the top of the list*/
}

Lebel* addToSymbolList(Lebel* list, Lebel* new_node)
{
	Lebel* p;

	p = list;
	if (!list)
	{
		/* Empty list; Let the new node be its head. */
		list = new_node;
	}
	else {
		/* The list is not empty; Find the tail. */
		while (p != NULL) {
			p = p->next;
		}
		p = new_node;
	}
	return list;
}
/**
* Func to free the lists
*/
void freeLebelList(Lebel* head)
{
	Lebel* p, * temp;
	p = temp = head;

	while (p)
	{
		temp = p;
		p = p->next;

		free(temp->lebel);
		temp->lebel = NULL;
		free(temp);
		free(p);
	}
	return;
} /* End of func */

void freeLineList(Line* head)
{
	Line* p, * temp;
	p = temp = head;

	while (p)
	{
		temp = p;
		p = p->next;


		free(temp->lebel);
		temp->lebel = NULL;
		free(temp);
		free(p);
	}
	return;
} /* End of func */


/*Search in lists*/

Lebel* searchInLebelList(Lebel* head, char* lebel)
{
	Lebel* temp = head;

	while (temp)
	{
		if (!strcmp(lebel, temp->lebel))
			return temp->lebel;

		temp = temp->next;
	}
	return NULL;
}

Line* searchInMainList(Line* head, char* lebel)
{
	Line* temp = head;

	while (temp)
	{
		if (!strcmp(lebel, temp->lebel))
			return temp->lebel;

		temp = temp->next;
	}
	return NULL;
}
/**
* Create new nodes
*/
Line* newLineNode(Line* node, int line, int instruction, char ARE)
{
	node = (Line*)malloc(sizeof(Line));
	if (!node)
		fatal_error(ErrorMemoryAlloc);
	node->lebel = (char*)malloc(sizeof(char));
	if (!node->lebel)
		fatal_error(ErrorMemoryAlloc);

	node->address = line;
	node->is_instruction = instruction;
	node->are = ARE;
	node->bcode.allBits = 0;
	node->next = NULL;
}
Lebel* NewLebelNode()
{
	Lebel* lebel = (Lebel*)malloc(sizeof(Lebel));
	if (!lebel)
		fatal_error(ErrorMemoryAlloc);

	lebel->lebel = NULL;
	lebel->line = 0;
	lebel->type = 0;
	lebel->next = NULL;
	return lebel;
}