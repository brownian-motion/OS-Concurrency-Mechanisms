#pragma once
#include <pthread>

extern static volatile unsigned int glob;

pthread_spinloc_t spinLock;

void init_spinlock(){
	pthread_spin_init(&spinLock, PTHREAD_PROCESS_PRIVATE);
}

void* increment_with_spinlock(void* arg){
	int numLoops = *((int *) arg);
	while(numLoops-- > 0){
		while(pthread_spin_trylock(&spinLock) != 0);
		glob++;
		pthread_spin_unlock(&spinLock);
	}
	return NULL;
}