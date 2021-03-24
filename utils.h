
#ifndef UTILS_H_
#define UTILS_H_



#define MAX_LINE_LENGTH 81
#define NUM_OF_COMMANDS 16
#define MAX_DATA_NUM 4096
#define NUM_OF_REG 7

#define IsBlank(c) ((c) == ' ' || (c) == '\t')
/*#define NextWord(x) while(*word == ' ' || *word == '\t') word++;/

/*
int IsBlank(char* c);*/
char* NextWord(char* x);

#endif