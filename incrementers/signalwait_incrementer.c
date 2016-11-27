#pragma once

#include <pthread.h>

extern volatile unsigned int glob;

pthread_cond_t hasThreadFinishedCondition;
// pthread_mutex_t mutex;

void init_signalwait(){
	pthread_cond_init(&condition, NULL);
	// pthread_mutex_init(&mutex, NULL);
}

//I have no idea what I'm doing
void* increment_with_signalwait(void* arg){
	int numLoops = *((int *) arg);

	while(glob % numLoops != 0)
		pthread_cond_wait(&condition);
	for(int i = 0 ; i < numLoops ; i++){
		glob++;
	}
	pthread_cond_signal(&condition);

	return NULL;
}