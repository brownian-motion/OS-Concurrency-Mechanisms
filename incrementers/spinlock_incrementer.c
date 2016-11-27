#pragma once
#include <pthread.h>

extern volatile unsigned int glob;

pthread_spinlock_t spinLock;

void init_spinlock(){
	pthread_spin_init(&spinLock, PTHREAD_PROCESS_PRIVATE);
}

/**
 * For `numLoop` number of times, busywaits for the spinlock to be ready, then locks, increments, and unlocks.
 * I deliberately put the critical section inside the loop, rather than surrounding the loop.
 * This way, different threads can increment without needing to complete their entire tasks.
 */
void* increment_with_spinlock(void* arg){
	int numLoops = *((int *) arg);
	while(numLoops-- > 0){
		while(pthread_spin_trylock(&spinLock) != 0);
		glob++;
		pthread_spin_unlock(&spinLock);
	}
	return NULL;
}