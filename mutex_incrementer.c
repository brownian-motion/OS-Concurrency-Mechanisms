#pragma once

#include <pthread.h>

volatile unsigned int mutex_counter;

pthread_mutex_t mutex;

int init_mutex(){
	if(pthread_mutex_init(&mutex, NULL) != 0){
		fprintf(stderr, "Failed to initialize mutex");
		return 1;
	}
	return 0;
}

void increment_with_mutex(unsigned int numTimes){
	while(numTimes-- > 0){
		pthread_mutex_lock(&mutex);
		mutex_counter++;
		pthread_mutex_unlock(&mutex);
	}
}

int get_mutex_counter_value(){
	return mutex_counter;
}