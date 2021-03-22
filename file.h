#ifndef FILE_H_
#define FILE_H_

#include <stdio.h>
#include "error.h"



#define MainFileEnding ".as"
#define ObjectFileEnding ".ob"
#define ExternFileEnding ".ext"
#define EntryFileEnding ".ent"

/*
* open a file
* save pointer to the file (full_file_name).
*  - modolary
*/
void open_file(const char* file_name, char* ending, char* mod);
/**
*
*/
char* get_file_name(const char* ending);
/**
*
*/
char* runOnLine();

/**
* Collect the next word.
*/
char* read_word(const char* line, const int line_num, FILE* fp);
/**
*
*/
char* get_file_name(const char* ending);
/**
*
*/
void close_file();
#endif
