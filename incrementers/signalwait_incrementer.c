#pragma once

#include <pthread.h>

extern volatile unsigned int glob;

pthread_cond_t hasThreadFinishedCondition;
pthread_mutex_t mutex;

void init_signalwait(){
	pthread_cond_init(&hasThreadFinishedCondition, NULL);
	pthread_mutex_init(&mutex, NULL);
}

//I have no idea what I'm doing
void* increment_with_signalwait(void* arg){
	int numLoops = *((int *) arg);

	pthread_mutex_lock(&mutex);
	while(glob % numLoops != 0)
		pthread_cond_wait(&hasThreadFinishedCondition, &mutex);
	int i;
	for(i = 0 ; i < numLoops ; i++){
		glob++;
	}
	pthread_cond_signal(&hasThreadFinishedCondition);
	pthread_mutex_unlock(&mutex);

	return NULL;
}