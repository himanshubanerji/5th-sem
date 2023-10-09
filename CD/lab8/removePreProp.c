#include "lexeme.h"

void removePreProps(char *inputfile) {

	FILE *fa, *fb;
	int ca, cb;

	fa = fopen(inputfile, "r");
	if (fa == NULL)
	{
		printf("Cannot open file \n");
		exit(0);
	}
	fb = fopen("output.c", "w+");
	ca = getc(fa);
	while (ca != EOF)
	{
		if (ca == ' ')
		{
			putc(ca, fb);
			while (ca == ' ')
				ca = getc(fa);
		}
		if (ca == '/')
		{
			cb = getc(fa);
			if (cb == '/')
			{
				while (ca != '\n')
					ca = getc(fa);
			}
			else if (cb == '*')
			{
				do
				{
					while (ca != '*')
						ca = getc(fa);
					ca = getc(fa);
				} while (ca != '/');
			}
			else
			{
				putc(ca, fb);
				putc(cb, fb);
			}
		}
		else
			putc(ca, fb);
		ca = getc(fa);
	}
	fclose(fa);
	fclose(fb);
	fa = fopen(inputfile, "r");
	if (fa == NULL)
	{
		printf("Cannot open file\n");
		exit(1);
	}
	fb = fopen("temp.c", "w+");
	ca = getc(fa);
	while (ca != EOF)
	{
		if (ca == '"')
		{
			putc(ca, fb);
			ca = getc(fa);
			while (ca != '"')
			{
				putc(ca, fb);
				ca = getc(fa);
			}
		}
		else if (ca == '#')
		{

			while (ca != '\n')
				ca = getc(fa);
			ca = getc(fa);
		}
		putc(ca, fb);
		ca = getc(fa);
	}
	fclose(fa);
	fclose(fb);
	fa = fopen("temp.c", "r");
	fb = fopen("output.c", "w");
	ca = getc(fa);
	while (ca != EOF)
	{
		putc(ca, fb);
		ca = getc(fa);
	}
	fclose(fa);
	fclose(fb);
	remove("temp.c");
}