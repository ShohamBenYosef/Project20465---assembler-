#include "error.h"
#include <stdio.h>
#include <stdlib.h>

/**
*
*/
void fatal_error(const char* message) {
	fprintf(stderr, "Fatal error: %s\n", message);
	exit(EXIT_FAILURE);
}