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
* Getting the name of the file. (adding the ending to the name that )
*/
char* get_file_name(const char* ending);
/**
* Copy the line to string so we can run on it
*/
char* runOnLine(FILE* fp);

/**
* Collect the next word.
*/
char* read_word(const char* line, const int line_num, FILE* fp);

/**
* closing the file
*/
void close_file();
#endif
