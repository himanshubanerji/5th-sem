#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX 100

struct ARRAY {
	int n;
	int arr[MAX];
};

void* threadRun(void *arg) {
	struct ARRAY *array = (struct ARRAY *)arg;

	int len = array->n;
	array->arr[0] = 0;
	array->arr[1] = 1;
	for(int i = 2; i < len; i++) {
		array->arr[i] = array->arr[i - 1] + array->arr[i - 2];
	}
}

int main() {
	struct ARRAY* fibo;

	fibo = malloc(sizeof(struct ARRAY));

	printf("Enter the number of fibonacci number: ");
	scanf("%d", &fibo->n);

	// thread creation
	pthread_t thread;
	pthread_create(&thread, NULL, threadRun, (void *)fibo);

	// thread join
	printf("child thread joined...\n");
	pthread_join(thread, NULL);

	printf("child thread ended...\n");
	printf("in main thread...\n");

	for(int i = 0; i < fibo->n; i++) {
		printf("%d ", fibo->arr[i]);
	}
	printf("\n");

	return 0;
}