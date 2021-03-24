
assembler: main.o file.o list.o error.o parse.o translate.o utils.o commands.o
	gcc -o assembler main.o file.o list.o error.o parse.o translate.o utils.o commands.o

list.o: list.c list.h
	gcc -c -ansi -Wall -pedantic list.c -lm

main.o: main.c
	gcc -c -ansi -Wall -pedantic main.c -lm

file.o: file.c file.h
	gcc -c -ansi -Wall -pedantic file.c -lm

error.o: error.c error.h
	gcc -c -ansi -Wall -pedantic error.c -lm

parse.o: parse.c parse.h
	gcc -c -ansi -Wall -pedantic parse.c -lm

translate.o: translate.c translate.h
	gcc -c -ansi -Wall -pedantic translate.c -lm

commands.o: commands.c commands.h
	gcc -c -ansi -Wall -pedantic commands.c -lm

utils.o: utils.c utils.h
	gcc -c -ansi -Wall -pedantic utils.c -lm