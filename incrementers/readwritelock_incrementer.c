#pragma once

extern static volatile unsigned int glob;

void init_readwritelock(){

}

void* increment_with_readwritelock(void* arg){
	int numLoops = *((int *) arg);
	while(numLoops-- > 0){
		
	}
	return NULL;
}