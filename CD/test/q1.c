#include <stdio.h>
#include <stdlib.h>

#define FILENAME_SIZE 100

int main() {
	FILE *r_fptr, *w_fptr;
	char read_filename[FILENAME_SIZE], write_filename[FILENAME_SIZE], ch;

	printf("Enter the name of the file to read: ");
	scanf("%s", read_filename);

	r_fptr = fopen(read_filename, "r");

	if(!r_fptr) {
		printf("File cannot be read!");
		exit(0);
	}

	printf("Enter the name of the file to be written to: ");
	scanf("%s", write_filename);

	w_fptr = fopen(write_filename, "w");

	if(!w_fptr) {
		printf("File cannot be opened to write!");
		exit(0);
	}


	while(ch != EOF) {
		ch = fgetc(r_fptr);
		if(ch == ' ' || ch == '\t') {
			while(ch == ' ' || ch == '\t') {
				ch = fgetc(r_fptr);
			}
			fputc(' ', w_fptr);
			fputc(ch, w_fptr);
		}
		else {
			fputc(ch, w_fptr);
		}
	}


	fclose(r_fptr);
	fclose(w_fptr);

	return 0;
}

