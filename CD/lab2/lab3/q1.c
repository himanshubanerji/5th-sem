#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SIZE 100

typedef struct Token {
	char op[10];
	char lexeme[SIZE];
	int row;
	int col;
}TOKEN;


void printArithmetic(char ari[5], FILE *ptr) {
	int row = 0;
	int col = 0;
	char ch = fgetc(ptr);
	while(ch != EOF) {
		if(ch == '\n') {
			row++;
			col = 0;
		}
		else {
			col++;
		}
		
		for(int i = 0; i < 5; i++) {
			if(ch == ari[i]) {
				printf("arithemetic found: %c\n", ch);
				printf("row: %d; col: %d\n", row, col);
			}
		}

		ch = fgetc(ptr);
	}
	
}


void removeDirectives(FILE *ptr1, FILE *ptr2) {
	char ch = getc(ptr1);
	while(ch != EOF) {
		if(ch == '#') {
			while(ch != '\n') {
				ch = getc(ptr1);
			}
			ch = getc(ptr1);
		}
		if(ch == '#') continue;

		fputc(ch, ptr2);
		ch = getc(ptr1);
	}
	fclose(ptr1);
	fclose(ptr2);
}

int main() {
	FILE *ptr1, *ptr2, *ptr_ans;

	char file1[SIZE], file2[SIZE];

	printf("read file: ");
	scanf("%s", file1);

	printf("write file: ");
	scanf("%s", file2);

	ptr1 = fopen(file1, "r");
	ptr2 = fopen("input1.txt", "w");
	ptr_ans = fopen(file2, "w");

	if(!ptr1 || !ptr2) {
		printf("error in read/write operation!");
		exit(1);
	}

	removeDirectives(ptr1, ptr2);

	char ari[5] = {'+', '-', '/', '*', '%'};
	char rel[6][3] = {"==", "<", ">", "<=", ">=", "!="};
	char logical[3][3] = {"&&", "||", "!"};
	char special[3] = {';', ',', '?'};
	char keywords[32][10] = {"auto", "double", "int", "struct",
	"break", "else", "long","switch", "case", "enum", "register",
	"typedef", "char","extern", "return", "union", "const", "float",
	"short", "unsigned", "continue", "for", "signed", "void",
	"default", "goto", "sizeof", "voltile", "do", "if", "static",
	"while"};

	ptr2 = fopen("input1.txt", "r");

	printArithmetic(ari, ptr2);


	return 0;
}