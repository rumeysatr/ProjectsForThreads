/*
Use a mutex to protect the shared variable.
Increment the counter in each thread using 
the mutex to avoid race conditions.
Observe the correct results.
*/

#include <pthread.h>
#include <stdio.h>

#define NUM_T 5
int counter = 0;
pthread_mutex_t lock;

void * func(void *arg)
{
	pthread_mutex_lock(&lock);
	counter++;
	printf("Counter: %d\n", counter);
	pthread_mutex_unlock(&lock);
	return NULL;
}

int main()
{
	pthread_t threads[NUM_T];

	pthread_mutex_init(&lock, NULL);

	for (int i = 0; i < NUM_T; i++)
		pthread_create(&threads[i], NULL, func, NULL);
	for (int i = 0; i < NUM_T; i++)
		pthread_join(threads[i], NULL);
	
	pthread_mutex_destroy(&lock);

	return 0;
}