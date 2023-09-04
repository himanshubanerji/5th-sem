/*

S -> aAcBe
A -> bA'
A' -> bA' | ε
B -> d

*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void S(char *str, int *curr);
void A(char *str, int *curr);
void Aprime(char *str, int *curr);
void B(char *str, int *curr);

void invalid() {
	printf("----ERROR!----\n");
	exit(0);
}

void valid() {
	printf("----SUCCESS!----\n");
	exit(0);
}

void B(char *str, int *curr) {
	if(str[*curr] == 'd') {
		*curr = *curr + 1;
	}
	else invalid();
}


void A(char *str, int *curr) {
	if(str[*curr] == 'b') {
		*curr = *curr + 1;
		Aprime(str, curr);
	}
	else invalid();
}

void Aprime(char *str, int *curr) {
	if(str[*curr] == 'b') {
		*curr = *curr + 1;
		Aprime(str, curr);
	}
}

void S(char *str, int *curr) {
	if(str[*curr] == 'a') {
		*curr = *curr + 1;
		A(str, curr);
		if(str[*curr] == 'c') {
			*curr = *curr + 1;
			B(str, curr);
			if(str[*curr] == 'e') {
				*curr = *curr + 1;
			} else invalid();
		} else invalid();
	} else invalid();
}

int main(int argc, char *argv[]) {
	if(argc < 2) {
		printf("usage %s <filename>\n", argv[0]);
		exit(1);
	}

	int curr = 0;
	char str[100];
	strcpy(str, argv[1]);

	S(str, &curr);

	if(str[curr] == '$') valid();
	else invalid();

	return 0;
}
