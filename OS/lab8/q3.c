#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>
#include <string.h>

#define MAX 100

struct ARRAY {
	int st;
	int end;
	bool prime[MAX];
};

void* SieveOfEratosthenes(void *arg)
{
	struct ARRAY *array = (struct ARRAY *)arg;

	memset(array->prime, true, sizeof(array->prime));

	for (int p = 2; p * p <= array->end; p++) {
		if (array->prime[p] == true) {
			for (int i = p * p; i <= array->end; i += p)
				array->prime[i] = false;
		}
	}
}

int main() {
	struct ARRAY* array;

	array = malloc(sizeof(struct ARRAY));

	printf("Enter start and end: ");
	scanf("%d %d", &array->st, &array->end);

	// thread creation
	pthread_t thread;
	pthread_create(&thread, NULL, SieveOfEratosthenes, (void *)array);

	// thread join
	printf("child thread joined...\n");
	pthread_join(thread, NULL);

	printf("child thread ended...\n");
	printf("in main thread...\n");

	for(int i = array->st; i <= array->end; i++) {
		if(i == 1) continue;
		if(array->prime[i]) printf("%d ", i);
	}
	printf("\n");

	return 0;
}