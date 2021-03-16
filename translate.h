/**
* translate.h
*/
#include <stdio.h>
#include "file.h"
#include "error.h"


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