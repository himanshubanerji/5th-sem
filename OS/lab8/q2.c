#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX 100

struct ARRAY {
	int n;
	int arr[MAX];
	int ans;
};

void* threadRun(void *arg) {
	struct ARRAY *array = (struct ARRAY *)arg;

	int len = array->n;

	for(int i = 0; i < len; i++) {
		array->ans += array->arr[i];
	}

}

int main() {
	struct ARRAY* array;

	array = malloc(sizeof(struct ARRAY));

	printf("Enter number of integers: ");
	scanf("%d", &array->n);
	printf("Enter only non-negative integers: ");
	for(int i = 0; i < array->n; i++) {
		scanf("%d", &array->arr[i]);
	}

	// thread creation
	pthread_t thread;
	pthread_create(&thread, NULL, threadRun, (void *)array);

	// thread join
	printf("child thread joined...\n");
	pthread_join(thread, NULL);

	printf("child thread ended...\n");
	printf("in main thread...\n");

	printf("Sum = %d\n", array->ans);

	return 0;
}