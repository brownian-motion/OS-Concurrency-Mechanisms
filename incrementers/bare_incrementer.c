#pragma once

extern volatile unsigned int glob;

/**
 * Increments a global variable with no respect to other threads.
 */
void* increment_with_no_lock(void* arg){
	int numLoops = *((int *) arg);
	while(numLoops-- > 0){
		glob++;
	}

	return 0;
}