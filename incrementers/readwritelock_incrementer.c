#pragma once

#include <pthread.h>

extern volatile unsigned int glob;

pthread_rwlock_t rwlock;

void init_readwritelock(){
	pthread_rwlock_init(&rwlock, NULL);
}

/**
 * Increments a global counter using a read/write lock to ensure that no thread writes to it at the same time.
 * The critical section is within the loop, so that only the part that increments is protected.
 * This is so that threads don't have to wait for others to be completely finished to start, just between
 * increments.
 * Specifically, this function ensures a write lock is obtained before reading, incrementing, and writing to `glob`.
 * It then releases that lock after one increment to let another thread increment in the meantime.
 */
void* increment_with_readwritelock(void* arg){
	int numLoops = *((int *) arg);
	while(numLoops-- > 0){
		pthread_rwlock_wrlock(&rwlock);
		glob++;
		pthread_rwlock_unlock(&rwlock);
	}
	return NULL;
}