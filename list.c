#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "list.h"
#include "error.h"
#include "utils.h"

#pragma warning(disable : 4996)


/* add */

Line* addToMainList(Line* list, Line* new_node)
{
	Line* p;

	p = list;
	if (!list)
		list = new_node;
	else
	{
		while (p->next)
			p = p->next;

		p->next = new_node;
	}

	return list; /* returning pointer to the top of the list*/
}

Lebel* addToSymbolList(Lebel* list, Lebel* new_node)
{
	Lebel* p;

	printf("in add to symbol.\n");
	p = list;
	if (!p)
	{
		printf("if list!=null\n");
		/* Empty list; Let the new node be its head. */
		list = new_node;
	}
	else {
		printf("else\n");
		/* The list is not empty; Find the tail. */
		while (p != NULL)
			p = p->next;

		p->next = new_node;
	}
	printf("return\n");
	return list;
}

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
} /* end of func */

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
} /* end of func */


/* search*/

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
	free(temp);
	return NULL;
}

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
}ã