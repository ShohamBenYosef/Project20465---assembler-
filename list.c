#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "list.h"
#include "error.h"
#include "utils.h"

Lebel* lebel_list_head;
Line* main_list_head;


/*func*/

Line* addToMainList(Line* main_list_head, Line* new_node);
Lebel* addToSymbolList(Lebel* lebel_list_head, Lebel* new_node);
void freeLebelList(Lebel* head);
void freeLineList(Line* head);
Lebel* searchInLebelList(Lebel* head, char* lebel);
Line* searchInMainList(Line* head, char* lebel);
Line* newLineNode(Line* node, int line, int instruction, char ARE);


/* add */

Line* addToMainList(Line* main_list_head, Line* new_node)
{
	Line* temp;

	temp = main_list_head;
	if (!main_list_head)
		main_list_head = new_node;
	else
	{
		while (temp->next)
			temp = temp->next;

		temp->next = new_node;
	}
	return main_list_head; /* returning pointer to the top of the list*/
}

Lebel* addToSymbolList(Lebel* lebel_list_head, Lebel* new_node)
{
	Lebel* temp;
	temp = lebel_list_head;
	if (!lebel_list_head)
		lebel_list_head = new_node;
	else {
		while (temp->next)
			temp = temp->next;

		temp->next = new_node;
	}
	return lebel_list_head;
}

/* free */

void freeLebelList(Lebel* head)
{
	Lebel* p, * temp;
	p = temp = head;

	while (p)
	{
		temp = p;
		p = p->next;

		free(temp->lebel);
		free(temp);
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

		free(temp->bcode.allBits);
		free(temp->lebel);
		free(temp);
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

