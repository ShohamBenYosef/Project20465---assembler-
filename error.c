#include "error.h"
#include "file.h"
#include <stdio.h>
#include <stdlib.h>


int errors_count;
/**
*
*/
void fatal_error(const char* message) {
	fprintf(stderr, "Fatal error: %s\n", message);
	exit(EXIT_FAILURE);
}

void error_log(char* msg, int line) {
	
		printf(stderr, "%s; The error is on line %d in %s\n",msg, line, full_file_name);
		errors_count++; 
}