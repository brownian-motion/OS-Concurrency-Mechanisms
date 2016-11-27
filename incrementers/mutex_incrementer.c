#pragma once

#include <pthread.h>

extern volatile unsigned int glob;

pthread_mutex_t mutex;

int init_mutex(void){
	if(pthread_mutex_init(&mutex, NULL) != 0){
		fprintf(stderr, "Failed to initialize mutex");
		return 1;
	}
	return 0;
}

void * increment_with_mutex(void * arg){
	int numLoops = *((int *) arg);
	while(numLoops-- > 0){
		pthread_mutex_lock(&mutex);
		glob++;
		pthread_mutex_unlock(&mutex);
	}
	return NULL;
}