#pragma once

#include <pthread.h>

extern volatile unsigned int glob;

pthread_rwlock_t rwlock;

void init_readwritelock(){
	pthread_rwlock_init(&rwlock, NULL);
}

void* increment_with_readwritelock(void* arg){
	int numLoops = *((int *) arg);
	while(numLoops-- > 0){
		pthread_rwlock_wrlock(&rwlock);
		glob++;
		pthread_rwlock_unlock(&rwlock);
	}
	return NULL;
}