
#include "lexeme.h"

struct token token;
FILE *f1;
char *rel[] = {"==", "!=", "<=", ">=", ">", "<"};
char *add[] = {"+", "-"};
char *mul[] = {"*", "/", "%"};

void errnoPrint(char *str, int row, int col) {
	printf("%s missing at row:%d col:%d\n",str, row, col);
	exit(1);
}

int isrel(char *w)
{
	int i;
	for (i = 0; i < sizeof(rel) / sizeof(char *); i++)
		if (strcmp(w, rel[i]) == 0)
			return 1;
	return 0;
}

int isadd(char *w)
{
	int i;
	for (i = 0; i < sizeof(add) / sizeof(char *); i++)
		if (strcmp(w, add[i]) == 0)
			return 1;
	return 0;
}

int ismul(char *w)
{
	int i;
	for (i = 0; i < sizeof(mul) / sizeof(char *); i++)
		if (strcmp(w, mul[i]) == 0)
			return 1;
	return 0;
}

int main(int argc, char *argv[]) {

	if(argc < 2) {
		printf("Usage: %s <input_filename>\n", argv[0]);
		exit(0);
	}

	// FILE *fa, *fb;
	// int ca, cb;

	// fa = fopen(argv[1], "r");
	// if (fa == NULL)
	// {
	// 	printf("Cannot open file \n");
	// 	exit(0);
	// }
	// fb = fopen("output.c", "w+");
	// ca = getc(fa);
	// while (ca != EOF)
	// {
	// 	if (ca == ' ')
	// 	{
	// 		putc(ca, fb);
	// 		while (ca == ' ')
	// 			ca = getc(fa);
	// 	}
	// 	if (ca == '/')
	// 	{
	// 		cb = getc(fa);
	// 		if (cb == '/')
	// 		{
	// 			while (ca != '\n')
	// 				ca = getc(fa);
	// 		}
	// 		else if (cb == '*')
	// 		{
	// 			do
	// 			{
	// 				while (ca != '*')
	// 					ca = getc(fa);
	// 				ca = getc(fa);
	// 			} while (ca != '/');
	// 		}
	// 		else
	// 		{
	// 			putc(ca, fb);
	// 			putc(cb, fb);
	// 		}
	// 	}
	// 	else
	// 		putc(ca, fb);
	// 	ca = getc(fa);
	// }
	// fclose(fa);
	// fclose(fb);
	// fa = fopen(argv[1], "r");
	// if (fa == NULL)
	// {
	// 	printf("Cannot open file\n");
	// 	return 0;
	// }
	// fb = fopen("temp.c", "w+");
	// ca = getc(fa);
	// while (ca != EOF)
	// {
	// 	if (ca == '"')
	// 	{
	// 		putc(ca, fb);
	// 		ca = getc(fa);
	// 		while (ca != '"')
	// 		{
	// 			putc(ca, fb);
	// 			ca = getc(fa);
	// 		}
	// 	}
	// 	else if (ca == '#')
	// 	{

	// 		while (ca != '\n')
	// 			ca = getc(fa);
	// 		ca = getc(fa);
	// 	}
	// 	putc(ca, fb);
	// 	ca = getc(fa);
	// }
	// fclose(fa);
	// fclose(fb);
	// fa = fopen("temp.c", "r");
	// fb = fopen("output.c", "w");
	// ca = getc(fa);
	// while (ca != EOF)
	// {
	// 	putc(ca, fb);
	// 	ca = getc(fa);
	// }
	// fclose(fa);
	// fclose(fb);
	// remove("temp.c");
	removePreProps(argv[1]);

	FILE *f1;

	f1 = fopen("output.c", "r");
	if (f1 == NULL)
	{
		printf("Error! File cannot be opened!\n");
		return 0;
	}
	while ((token = getNextToken(f1)).row != -1)
	{
		if (strcmp(token.lexeme, "main") == 0)
		{
			program(argv[1]);
			break;
		}
	}
	fclose(f1);
}

void program(char *file_name)
{
	if (strcmp(token.lexeme, "main") == 0)
	{
		token = getNextToken(f1);
		if (strcmp(token.lexeme, "(") == 0)
		{
			token = getNextToken(f1);
			if (strcmp(token.lexeme, ")") == 0)
			{
				token = getNextToken(f1);
				if (strcmp(token.lexeme, "{") == 0)
				{
					token = getNextToken(f1);
					declarations();
					statementlist();
					if (strcmp(token.lexeme, "}") == 0)
					{
						printf("[+]Success: \"%s\" compiled successfully\n", file_name);
						return;
					}
					else errnoPrint("}", token.row, token.col);
				}
				else errnoPrint("{", token.row, token.col);
			}
			else errnoPrint(")", token.row, token.col);
		}
		else errnoPrint("(", token.row, token.col);
	}
}

void declarations()
{
	if (isdtype(token.lexeme) == 0)
		return;
	datatype();
	idlist();
	if (strcmp(token.lexeme, ";") == 0)
	{
		token = getNextToken(f1);
		declarations();
	}
	else errnoPrint(";", token.row, token.col);
}

void datatype()
{
	if (strcmp(token.lexeme, "int") == 0)
	{
		token = getNextToken(f1);
		return;
	}
	else if (strcmp(token.lexeme, "char") == 0)
	{
		token = getNextToken(f1);
		return;
	}
	else errnoPrint(token.lexeme, token.row, token.col);
}

void idlist()
{
	if (strcmp(token.type, "identifier") == 0)
	{
		token = getNextToken(f1);
		idlistprime();
	}
	else errnoPrint("identifier", token.row, token.col);
}

void idlistprime()
{
	if (strcmp(token.lexeme, ",") == 0)
	{
		token = getNextToken(f1);
		idlist();
	}
	if (strcmp(token.lexeme, "[") == 0)
	{
		token = getNextToken(f1);
		if (strcmp(token.type, "number") == 0)
		{
			token = getNextToken(f1);
			if (strcmp(token.lexeme, "]") == 0)
			{
				token = getNextToken(f1);
				if (strcmp(token.lexeme, ",") == 0)
				{
					token = getNextToken(f1);
					idlist();
				}
				else
					return;
			}
		}
	}
	else
		return;
}

void statementlist()
{
	if (strcmp(token.type, "identifier") != 0)
		return;
	statement();
	statementlist();
}

void statement()
{
	assignstat();
	if (strcmp(token.lexeme, ";") == 0)
	{
		token = getNextToken(f1);
		return;
	}
}

void assignstat()
{
	if (strcmp(token.type, "identifier") == 0)
	{
		token = getNextToken(f1);
		if (strcmp(token.lexeme, "=") == 0)
		{
			token = getNextToken(f1);
			expn();
		}
		else errnoPrint("=", token.row, token.col);
	}
	else errnoPrint("identifier", token.row, token.col);
}

void expn()
{
	simpleexp();
	eprime();
}

void eprime()
{
	if (isrel(token.lexeme) == 0)
		return;
	relop();
	simpleexp();
}

void simpleexp()
{
	term();
	seprime();
}

void seprime()
{
	if (isadd(token.lexeme) == 0)
		return;
	addop();
	term();
	seprime();
}

void term()
{
	factor();
	tprime();
}

void tprime()
{
	if (ismul(token.lexeme) == 0)
		return;
	mulop();
	factor();
	tprime();
}

void factor()
{
	if (strcmp(token.type, "identifier") == 0)
	{
		token = getNextToken(f1);
		return;
	}
	else if (strcmp(token.type, "number") == 0)
	{
		token = getNextToken(f1);
		return;
	}
}

void relop()
{
	if (strcmp(token.lexeme, "==") == 0)
	{
		token = getNextToken(f1);
		return;
	}
	if (strcmp(token.lexeme, "!=") == 0)
	{
		token = getNextToken(f1);
		return;
	}
	if (strcmp(token.lexeme, "<=") == 0)
	{
		token = getNextToken(f1);
		return;
	}
	if (strcmp(token.lexeme, ">=") == 0)
	{
		token = getNextToken(f1);
		return;
	}
	if (strcmp(token.lexeme, "<") == 0)
	{
		token = getNextToken(f1);
		return;
	}
	if (strcmp(token.lexeme, ">") == 0)
	{
		token = getNextToken(f1);
		return;
	}
}

void addop()
{
	if (strcmp(token.lexeme, "+") == 0)
	{
		token = getNextToken(f1);
		return;
	}
	if (strcmp(token.lexeme, "-") == 0)
	{
		token = getNextToken(f1);
		return;
	}
}

void mulop()
{
	if (strcmp(token.lexeme, "*") == 0)
	{
		token = getNextToken(f1);
		return;
	}
	if (strcmp(token.lexeme, "/") == 0)
	{
		token = getNextToken(f1);
		return;
	}
	if (strcmp(token.lexeme, "*") == 0)
	{
		token = getNextToken(f1);
		return;
	}
}