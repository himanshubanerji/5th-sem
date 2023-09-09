#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX 100

struct ARRAY {
	int n;
	int esum;
	int osum;
	int arr[MAX];
};

void* threadRun1(void *arg) {
	struct ARRAY *array = (struct ARRAY *)arg;

	int len = array->n;

	for(int i = 0; i < len; i++) {
		if(!(array->arr[i] & 1)) array->esum += array->arr[i];
	}

}

void* threadRun2(void *arg) {
	struct ARRAY *array = (struct ARRAY *)arg;

	int len = array->n;

	for(int i = 0; i < len; i++) {
		if(array->arr[i] & 1) array->osum += array->arr[i];
	}

}

int main() {
	struct ARRAY* array;

	array = malloc(sizeof(struct ARRAY));

	printf("Enter number of integers: ");
	scanf("%d", &array->n);
	printf("Enter array: ");
	for(int i = 0; i < array->n; i++) {
		scanf("%d", &array->arr[i]);
	}

	// thread creation
	pthread_t thread1;
	pthread_create(&thread1, NULL, threadRun1, (void *)array);

	pthread_t thread2;
	pthread_create(&thread2, NULL, threadRun2, (void *)array);

	// thread join
	printf("child thread joined...\n");
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);

	printf("child thread ended...\n");
	printf("in main thread...\n");

	printf("Even sum: %d\n", array->esum);
	printf("Odd sum: %d\n", array->osum);

	return 0;
}