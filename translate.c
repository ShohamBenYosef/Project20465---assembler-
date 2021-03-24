/*
* translate.c
*/

#include "asm.h"
#include "utils.h"
#include "file.h"
#include "error.h"
#include "list.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


/* func */
int parse2();
void printEnt(FILE* name_file);
void printExt(FILE* name_file);
void printObjectFile(FILE* file_name);
int addTargetToSource(const Line* node);


/**
*
*/
int parse2(char* file_name)
{
	printf(" IN PARSE2() --  \n");
	/* file to print on */
	FILE* obOut, * extOut, * entOut;


	/* Temp lebels */
	Lebel* tmp_lebel = parser_data.Shead;
	Lebel* fnd_lebel = parser_data.Shead;
	/* Nodes for the lists - main */
	Line* node = parser_data.Mhead;

	/* Flags*/
	int empty_entry = 0, empty_extern = 0;
	/* Counters that hold the num of ent and ext*/
	int entry_flag = 0, extern_flag = 0;


	tmp_lebel = tmp_lebel->next;
	printf(" after declelrations.  \n");
	
	printf("tmp_lebel: %s\n", &tmp_lebel->lebel);

	/* run on symbol list with tmp_lebel as a pointer */
	while (tmp_lebel)
	{
		printf("IN WHILE \n");
		/* check entry type */
		if (tmp_lebel->type == entryType)
		{
			/* run on symbol list with fnd_lebel as a pointer */
			printf("  in if in while  ----   entry\n");
			while (fnd_lebel)
			{
				printf(" run on symbol lebel \n");
				entry_flag = 1;
				if (!strcmp(tmp_lebel->lebel, fnd_lebel->lebel))
				{
					fnd_lebel->line = tmp_lebel->line;
					empty_entry = 0;
				}
				fnd_lebel = fnd_lebel->next;
			}/* End of inner while */
			fnd_lebel = parser_data.Shead;

			while (node)
			{
				if (!strcmp(tmp_lebel->lebel, node->lebel))
				{
					node->address = tmp_lebel->line;
					node->are = 'E';
					empty_entry = 0;
				}
			}
			if (empty_entry == 1)
				error_log("Error, entry lebel has no.... ", -100);
		}


		/* check extern type */
		if (tmp_lebel->type == externType)
		{
			extern_flag = 1;
			while (fnd_lebel)
			{
				if (!strcmp(tmp_lebel->lebel, fnd_lebel->lebel))
				{
					fnd_lebel->line = tmp_lebel->lebel = 0;
					empty_extern = 0;
				}
				fnd_lebel = fnd_lebel->next;
			}
			fnd_lebel = parser_data.Shead;

			while (node)
			{
				if (!strcmp(tmp_lebel->lebel, node->lebel))
				{
					node->bcode.allBits = 0;
					node->are = 'E';
					empty_extern = 0;
				}
				node = node->next;
			}
			node = parser_data.Mhead;
			if (empty_extern == 1)
				error_log("Error, extern lebel has no.... ", -100);
		}
		tmp_lebel = tmp_lebel->next;

	}/* end of while loop */




	/* run on the main line and check if theres any MachineCode missing */
	while (tmp_lebel)
	{
		while (node)
		{
			if (strcmp(node->lebel, tmp_lebel))
			{
				node->bcode.allBits = tmp_lebel->line;
				node->are = 'E';
			}
			node = node->next;
		}
		node = parser_data.Mhead;

		tmp_lebel = tmp_lebel->next;
	}

	/* last check of error before print */
	if (parser_data.errors > 0)
		fatal_error(ErrorInAssemblyCode);


	/* Entry lebel */
	if (entry_flag > 0)
	{
		open_file(parser_data.file_name_base, EntryFileEnding, "\"w\"");
		printEnt(file);
		fclose(file);
	}
	/* Extern lebel*/
	if (extern_flag > 0)
	{
		open_file(parser_data.file_name_base, ExternFileEnding, "\"w\"");
		printExt(file);
		fclose(file);
	}

	/* Object. */
	open_file(parser_data.file_name_base, ObjectFileEnding, "\"w\"");
	printObjectFile(file);
	fclose(file);

	/* Closing the prog */
	freeLebelList(parser_data.Shead);
	freeLineList(parser_data.Shead);
	printf(" END OF %s FILE", parser_data.file_name_base);

	return 1;
}/* end of func */

/**
*
*/
void printEnt(FILE* name_file)
{
	Lebel* temp_lebel = parser_data.Shead;

	while (temp_lebel)
	{
		if (temp_lebel->type == entryType)
			fprintf(name_file, "%s\t%04d\n", temp_lebel->lebel, temp_lebel->line);

		temp_lebel = temp_lebel->next;
	}/* end of while*/
	/* return fnd back to the start. */
	temp_lebel = parser_data.Shead;
}

/**
*
*/
void printExt(FILE* name_file)
{
	Lebel* temp_lebel = parser_data.Shead;
	Lebel* fnd_lebel = parser_data.Shead;


	while (temp_lebel)
	{
		if (temp_lebel->type == externType)
		{
			while (fnd_lebel)
			{
				if (!strcmp(fnd_lebel->lebel, temp_lebel->lebel))
					fprintf(name_file, "%s\t%04d\n", fnd_lebel->lebel, fnd_lebel->line);

				fnd_lebel = fnd_lebel->next;
			}
			/* return fnd back to the start. */
			fnd_lebel = parser_data.Shead;
		}/* end of  if condition */

		temp_lebel = temp_lebel->next;
	}/* end of while*/
}

/**
*
*/
void printObjectFile(FILE* file_name)
{
	Line* temp = parser_data.Mhead;

	fprintf(file_name, "\t\t\t\t%d\t%d\n", parser_data.IC, parser_data.DC);
	while (temp)
	{

		if (temp->is_instruction)
			fprintf(file_name, "%04d\t%04X\t%c", temp->address, temp->bcode.allBits, temp->are);

		else
			fprintf(file_name, "%04d\t%01X%01X%01X\t%c", temp->address, temp->bcode.separateBits.opcode, temp->bcode.separateBits.func, addTargetToSource(temp), temp->are);

		temp = temp->next;
	}

}

/**
*
*/
int addTargetToSource(const Line* node)
{
	int res = 0;
	res += (node->bcode.separateBits.source);

	if (node->bcode.separateBits.target == 1)
		res += 4;
	if (node->bcode.separateBits.target == 2)
		res += 8;
	if (node->bcode.separateBits.target == 3)
		res += 12;

	return res;
}



void printSymbollist()
{
	printf(" 1\n");
	Line* temp = parser_data.Shead;
	printf(" temp.shead: %s\n", parser_data.Shead);
	while (temp != NULL)
	{
		printf(" x\n");
		printf("temp->lebel: %s\n", &temp->lebel);
		temp = temp->next;
	}
}



void printMainlist()
{
	printf(" 1\n");
	Line* temp = parser_data.Mhead;
	printf(" temp.shead: %s\n", parser_data.Mhead->bcode);
	while (temp->address )
	{
		printf(" x\n");
		printf("temp->lebel: %s\n", &temp->address);
		temp = temp->next;
	}
}