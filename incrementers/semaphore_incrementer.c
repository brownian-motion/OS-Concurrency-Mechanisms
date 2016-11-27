#pragma once

#include "semaphore.h"

extern volatile unsigned int glob;

sem_t semaphore;

void init_semaphore(){
	sem_init(&semaphore, 0, 1);
}

/**
 * Increments a global variable using a semaphore to make sure that no thread accesses it at the same time.
 * The critical section is within the loop; it only protects the code that actually increments.
 * Specifically, it waits on the semaphore using sem_wait until another thread declares sem_post.
 */
void* increment_with_semaphore(void * arg){
	int numLoops = *((int*)arg);
	while(numLoops-- > 0){
		sem_wait(&semaphore);
		glob++;
		sem_post(&semaphore);
	}
	return NULL;
}