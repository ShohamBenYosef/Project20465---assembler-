
#include "asm.h"
#include "file.h"
#include "error.h"
#include "list.h"
#include "translate.h"
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h> /*for alphanomeric*/
#include <string.h>

extern main_list_head, lebel_list_head;

void main()
{
	Line* line1, * line2, * line3,* temp;

	newLineNode(line1, 1, 1, 'a');
	line1->lebel = "MAIN:";
	newLineNode(line2, 2, 1, 'a');
	line2->lebel = "LEBEL:";
	newLineNode(line3, 3, 1, 'a');
	line3->lebel = "STR:";

	temp = main_list_head;
	while (temp)
	{
		printf("the first is %d with lebel %s",line1->address, line1->lebel);
		temp = temp->next;
	}


}