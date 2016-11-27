#pragma once

#include <pthread.h>

extern volatile unsigned int glob;

pthread_cond_t condition;
// pthread_mutex_t mutex;

void init_signalwait(){
	pthread_cond_init(&condition, NULL);
	// pthread_mutex_init(&mutex, NULL);
}

//I have no idea what I'm doing
void* increment_with_signalwait(void* arg){
	/*
	int numLoops = *((int *) arg);
	while(numLoops-- > 0){
		while(/*condition is false*//*)
			pthread_cond_wait(&condition);

		pthread_cond_signal(&condition);
		condition = 1;
	}*/
		fprintf(stderr,"Not done with signalwait yet");

	return NULL;
}