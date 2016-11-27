#pragma once

#include <pthread>

extern static volatile unsigned int glob;

pthread_rwlock_t rwlock;

void init_readwritelock(){
	pthread_rwlock_init(&rwlock, NULL);
}

void* increment_with_readwritelock(void* arg){
	int numLoops = *((int *) arg);
	while(numLoops-- > 0){
		pthread_rwlock_wrlock(&wrlock);
		glob++;
		pthread_rwlock_unlock(&wrlock);
	}
	return NULL;
}