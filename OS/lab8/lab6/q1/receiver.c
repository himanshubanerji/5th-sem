#include "../bits/stdc++.h"

bool checkPalin(char *num) {
	int n = strlen(num) - 1;

	for(int i = 0; i < n / 2; i++) {
		if(num[i] != num[n - i - 1]) return false;
	}

	return true;
}

int main()
{
	int running = 1;
	int msgid;
	struct my_msg_st some_data;
	long int msg_to_receive = 0;
	msgid = msgget((key_t)1234, 0666 | IPC_CREAT);
	if (msgid == -1) {
		fprintf(stderr, "msgget failed with error: %d\n", errno);
		exit(EXIT_FAILURE);
	}
	while(running) {
		if (msgrcv(msgid, (void *)&some_data, BUFSIZ,
			msg_to_receive, 0) == -1) {
			fprintf(stderr, "msgrcv failed with error: %d\n", errno);
		exit(EXIT_FAILURE);
	}

	char *num = some_data.some_text;

	int number = atoi(num);

	if(checkPalin(num)) printf("%d is palindrome!\n", number);
	else printf("%d is not palindrome!\n", number);

	if (strncmp(some_data.some_text, "end", 3) == 0) {
		running = 0;
	}
}
if (msgctl(msgid, IPC_RMID, 0) == -1) {
	fprintf(stderr, "msgctl(IPC_RMID) failed\n");
	exit(EXIT_FAILURE);
}
exit(EXIT_SUCCESS);
}