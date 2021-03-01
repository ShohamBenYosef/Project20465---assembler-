/*
* file.h
*/

#define FileEnding ".as"
/**/
char* full_file_name;
/**/

/*
* open a file for reading.
* save pointer to the file in global variable (full_file_name).
*/
void open_file(const char* file_name);

/*
* closing the file. (full_file_name)
*/
void close_file();