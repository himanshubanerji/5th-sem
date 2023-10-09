
#ifndef LEXEME_H
#define LEXEME_H

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

struct token
{
	char lexeme[128];
	unsigned int row, col;
	char type[64];
};
struct sttable
{
	int sno;
	char lexeme[128];
	char dtype[64];
	char type[64];
	int size;
};

int isKeyword(char*);
int isdtype(char*);
void newLine();
void printTable(struct sttable*, int);
int findTable(struct sttable*, char*, int);
struct sttable fillTable(int, char*, char*, char*, int);
void fillToken(struct token*, char, int, int, char*);
int charIs(int, const char*);
int sz(char*);
struct token getNextToken(FILE*);

void program(char*);
void declarations();
void datatype();
void idlist();
void idlistprime();
void assignstat();
void statementlist();
void statement();
void expn();
void eprime();
void simpleexp();
void seprime();
void term();
void tprime();
void factor();
void relop();
void addop();
void mulop();

void removePreProps(char*);

#endif