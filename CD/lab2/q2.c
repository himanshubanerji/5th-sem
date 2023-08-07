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

	ch = getc(r_fptr);
	while(ch != EOF) {
		if(ch == '#') {
			while(ch != '\n') {
				ch = getc(r_fptr);
			}
			// to discard the newline :)
			ch = getc(r_fptr);
		}
		if(ch == '#') continue;

		fputc(ch, w_fptr);
		ch = getc(r_fptr);
	}


	fclose(r_fptr);
	fclose(w_fptr);

	return 0;
}
