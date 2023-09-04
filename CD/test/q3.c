#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define FILENAME_SIZE 100

int compare(char buffer[], char keywords[32][10]){
	for(int i=0;i<32;i++){
		if(strcmp(buffer, keywords[i]) == 0){
			return 1;
		}
	}
	return 0;
}

int main() {
	char keywords[32][10] = {"auto", "double", "int", "struct",
		"break", "else", "long","switch", "case", "enum", "register",
		"typedef", "char","extern", "return", "union", "const", "float",
		"short", "unsigned", "continue", "for", "signed", "void",
		"default", "goto", "sizeof", "voltile", "do", "if", "static",
		"while"};


	FILE* fin = fopen("q1.c","r");
	if(fin == NULL){
		printf("Cannot find file!\n");
		exit(0);
	}
	char buffer[100], c = 0;
	int i = 0;
	while(c != EOF){
		if(isalpha(c) != 0){
			while(isalpha(c) != 0){
				c = fgetc(fin);
				if(isalpha(c) != 0)
					buffer[i++] = c;
			}
			buffer[i] = '\0';
			if(compare(buffer, keywords) == 1){
				for(int j=0;j<i;j++){
					printf("%c", toupper(buffer[j]));
				}
				printf("\n");
			}
			i = 0;
			buffer[0] = '\0';
		}
		else{
			c = fgetc(fin);
			if(isalpha(c) != 0)
				buffer[i++] = c;
		}
	}

	fclose(fin);

	return 0;
}
