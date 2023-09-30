#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <sys/wait.h>

#define MAX_TEXT 512
#define TEXT_SZ 2048

// struct shared_use_st {
// 	int written_by_you;
// 	char some_text[TEXT_SZ];
// };

struct shared_use_st{
	char alphabet;
};

struct my_msg_st {
	long int my_msg_type;
	char some_text[BUFSIZ];
};
