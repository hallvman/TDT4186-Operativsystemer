# Makefile for first lex example
CC = gcc 
LEX = flex
yacc = bison
CFLAGS = -g

all: compilers-pe2

lex.yy.c: compilers-pe2.l
	lex compilers-pe2.l

compilers-pe2: lex.yy.c 
	gcc -o $@ $< -I. -ll

clean:
	-@rm lex.yy.c compilers-pe2  
