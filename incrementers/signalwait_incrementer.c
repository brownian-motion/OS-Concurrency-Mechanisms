#pragma once

#include <pthread>

extern static volatile unsigned int glob;

pthread_cond_t condition;
pthread_mutex_t mutex;

void init_signalwait(){
	pthread_cond_init(&condition, NULL);
	pthread_mutex_init(&mutex, NULL);
}

//I have no idea what I'm doing
void* increment_with_signalwait(void* arg){
	int numLoops = *((int *) arg);
	while(numLoops-- > 0){
		pthread_lock_mutex(&mutex);
		while(/*condition is false*/)
			pthread_cond_wait(&condition,&mutex);

		pthread_cond_signal(&condition,&mutex);
		pthread_unlock_mutex(&mutex);
		condition = 1;
	}

	return NULL;
}