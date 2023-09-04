/*

S -> UVW
U -> (S) | aSb | d
V -> aV | ε
W -> cW | ε

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void S(char *str, int *curr);
void U(char *str, int *curr);
void V(char *str, int *curr);
void W(char *str, int *curr);

void invalid() {
	printf("----ERROR!----\n");
	exit(0);
}

void valid() {
	printf("----SUCCESS!----\n");
	exit(0);
}

void V(char *str, int *curr) {
	if(str[*curr] == 'a') {
		*curr = *curr + 1;
		V(str, curr);
	}
}

void W(char *str, int *curr) {
	if(str[*curr] == 'c') {
		*curr = *curr + 1;
		W(str, curr);
	}
}

void U(char *str, int *curr) {
	if(str[*curr] == '(') {
		*curr = *curr + 1;
		S(str, curr);
		if(str[*curr] == ')') {
			*curr = *curr + 1;
			return;
		}
		else invalid();
	}

	else if(str[*curr] == 'a') {
		*curr = *curr + 1;
		S(str, curr);
		if(str[*curr] == 'b') {
			*curr = *curr + 1;
			return;
		} else invalid();
	}

	else if(str[*curr] == 'd') {
		*curr = *curr + 1;
		return;
	}

	else invalid();
}

void S(char *str, int *curr) {
	U(str, curr);
	V(str, curr);
	W(str, curr);
}

int main() {
	int curr = 0;
	char str[100];

	printf("Enter string: ");
	scanf("%s", str);

	S(str, &curr);

	if(str[curr] == '$') valid();
	else invalid();



	return 0;
}
