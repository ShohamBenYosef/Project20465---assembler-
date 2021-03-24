/**
* translate.h
*/
#ifndef TRANSLATE_H_
#define TRANSLATE_H_

#include <stdio.h>
#include "file.h"
#include "error.h"
#include "utils.h"

enum { entryFile, externFile, objectFile };


#define OpenFile(file, ending, mod) {\
	char* file_name = get_file_name(extension);\
	file = fopen(file_name, mod);\
	if (!file) {\
		fprintf(stderr, ErrorCantRead, file_name);\
		fprintf(stderr, "\n");\
		free(file_name);\
		exit(EXIT_FAILURE);\
	}\
	free(file_name);\
}


/***
*
*/
int parse2(FILE* fp);
/**
*
*/
void printEnt(FILE* name_file);
/**
*
*/
void printExt(FILE* name_file);
/**
*
*/
void printObjectFile(FILE* file_name);
/**
*
*/
int addTargetToSource(const Line* node);


void printSymbollist();

void printMainlist();


#endif