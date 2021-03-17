
/*
* translate.c
*/

#include "asm.h"
#include "file.h"
#include "error.h"
#include "list.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

extern main_list_head, lebel_list_head;
extern DCF, ICF;
extern fp;



/* func */
int parse2();
void printEnt(FILE* name_file);
void printExt(FILE* name_file);
void printObjectFile(FILE* file_name);
int addTargetToSource(const Line* node);


/**
*
*/
int parse2()
{

	/* file to print on */
	FILE* obOut, * extOut, * entOut;


	/* temp lebels */
	Lebel* tmp_lebel = lebel_list_head;
	Lebel* fnd_lebel = lebel_list_head;
	/* nodes for the lists - main */
	Line* node = main_list_head;


	int empty_entry = 0, empty_extern = 0;
	/* counters that hold the num of ent and ext*/
	int entry_flag = 0, extern_flag = 0;


	/* run on symbol list with tmp_lebel as a pointer */
	while (tmp_lebel)
	{
		/* check entry type */
		if (tmp_lebel->type == entryType)
		{
			/* run on symbol list with fnd_lebel as a pointer */
			while (fnd_lebel)
			{
				entry_flag = 1;
				if (!strcmp(tmp_lebel->lebel, fnd_lebel->lebel))
				{
					fnd_lebel->line = tmp_lebel->line;
					empty_entry = 0;
				}
				fnd_lebel = fnd_lebel->next;
			}/* End of inner while */
			fnd_lebel = lebel_list_head;

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
		tmp_lebel = tmp_lebel->next;




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
			fnd_lebel = lebel_list_head;

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
			if (empty_extern == 1)
				error_log("Error, extern lebel has no.... ", -100);
		}
		node = main_list_head;


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
		node = main_list_head;

		tmp_lebel = tmp_lebel->next;
	}

	/* last check of error before print */
	if (errors_count > 0)
		fatal_error(ErrorInAssemblyCode);


	/* Entry lebel */
	if (entry_flag > 0)
	{
		entOut = open_file(full_file_name, EntryFileEnding, "\"w\"");
		printEnt(entOut);
		close_file(full_file_name, EntryFileEnding);
	}
	/* Extern lebel*/
	if (extern_flag > 0)
	{
		extOut = open_file(full_file_name, ExternFileEnding, "\"w\"");
		printExt(extOut); /* TODO!*/
		close_file(full_file_name, ExternFileEnding);
	}

	/* Object. */
	obOut = open_file(full_file_name, ObjectFileEnding, "\"w\"");
	printObjectFile(obOut);
	close_file(full_file_name, ObjectFileEnding);

	/* Closing the prog */
	freeLebelList(lebel_list_head);
	freeLineList(main_list_head);
	printf(" END OF %s FILE", full_file_name);

	return 1;
}/* end of func */

/**
*
*/
void printEnt(FILE* name_file)
{
	Lebel* temp_lebel = lebel_list_head;

	while (temp_lebel)
	{
		if (temp_lebel->type == entryType)
			fprintf(name_file, "%s\t%04d\n", temp_lebel->lebel, temp_lebel->line);

		temp_lebel = temp_lebel->next;
	}/* end of while*/
	/* return fnd back to the start. */
	temp_lebel = lebel_list_head;
}

/**
*
*/
void printExt(FILE* name_file)
{
	Lebel* temp_lebel = lebel_list_head;
	Lebel* fnd_lebel = lebel_list_head;


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
			fnd_lebel = lebel_list_head;
		}/* end of  if condition */

		temp_lebel = temp_lebel->next;
	}/* end of while*/
}

/**
*
*/
void printObjectFile(FILE* file_name)
{
	Line* temp = main_list_head;

	fprintf(file_name, "\t\t\t\t%d\t%d\n", ICF, DCF);
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