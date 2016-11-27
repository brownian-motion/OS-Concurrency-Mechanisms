#pragma once

#include "semaphore.h"

extern static volatile unsigned int glob;

sem_t semaphore;

void init_semaphore(){
	sem_init(&semaphore, NULL, 1);
}

void* increment_with_semaphore(void * arg){
	int numLoops = *((int*)arg);
	while(numLoops-- > 0){
		sem_wait(&semaphore);
		glob++;
		sem_post(&semaphore);
	}
	return NULL;
}