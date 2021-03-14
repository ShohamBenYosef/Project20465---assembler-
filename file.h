#include <stdio.h>
#include "error.h"
#include "list.h"

#define MainFileEnding ".as"
#define ObjectFileEnding ".ob"
#define ExternFileEnding ".ext"
#define EntryFileEnding ".ent"

#define MAX_LINE_LENGTH 81

/**/
char* full_file_name;


/*
* open a file for reading.
* save pointer to the file in global variable (full_file_name).
*/
FILE* open_file(const char* file_name, char* ending, char* mod);

/**
*
*/
char* runOnLine();

/**
* Collect the next word.
*/
char* read_word(const char* line, const int line_num, FILE* fp);

/*
* closing the file. (full_file_name)
*/
void close_file();