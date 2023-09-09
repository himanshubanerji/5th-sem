#include <stdio.h>
#include <pthread.h>

void* threadCode(void *args) {
	int *cnt = (int *)args;
	printf("In thread code %d\n", *cnt);
}

int main() {
	pthread_t thread;

	int num = 1;
	pthread_create(&thread, 0, &threadCode, (void*)&num);

	pthread_join(thread, NULL);
	printf("In main thread\n");

	return 0;
}
