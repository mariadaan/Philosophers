#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

int global = 0;
pthread_mutex_t mutex;


void *routine()
{
	pthread_mutex_lock(&mutex);
	for (int i = 0; i < 1000000; i++){
		global++;
		
	}
	printf("%d ", global);
	pthread_mutex_unlock(&mutex);
}

int main(int argc, char *argv[])
{
	pthread_t t1;
	pthread_t t2;

	pthread_mutex_init(&mutex, NULL);
	pthread_create(&t1, NULL, &routine, NULL);
	pthread_create(&t2, NULL, &routine, NULL);
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	pthread_mutex_destroy(&mutex);

	return (0);
}