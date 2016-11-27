/*************************************************************************\
*                  Copyright (C) Michael Kerrisk, 2016.                   *
*                                                                         *
* This program is free software. You may use, modify, and redistribute it *
* under the terms of the GNU General Public License as published by the   *
* Free Software Foundation, either version 3 or (at your option) any      *
* later version. This program is distributed without any warranty.  See   *
* the file COPYING.gpl-v3 for details.                                    *
\*************************************************************************/

#include <pthread.h>
#include <time.h>
#include "include/dependencies.h"

#include "incrementers/mutex_incrementer.c"
#include "incrementers/semaphore_incrementer.c"
#include "incrementers/spinlock_incrementer.c"
#include "incrementers/readwritelock_incrementer.c"
#include "incrementers/signalwait_incrementer.c"
#include "incrementers/bare_incrementer.c"

#define streq(s1, s2) (strcmp(s1, s2) == 0)

volatile unsigned int glob = 0;   /* "volatile" prevents compiler optimizations
                                   of arithmetic operations on 'glob' */

static void *(* incrementer_func)(void *) = 0; //what function each thread should use, to be set by main when parsing args

void printUsage(){
	fprintf(stderr,"Usage: %s %s %s %s\n","./hw5","<num-loops>","<num-threads>","<concurrency-method>");
	fprintf(stderr,"Valid Concurrency methods are:\n\tnone\n\tmutex\n\tspinlock\n\treadwritelock\n\tsignalwait\n\tsemaphore\n");
}

int
main(int argc, char *argv[])
{
	struct timespec spec;
	int numLoops, threadStatus, numThreads;

	if(argc == 2 && streq(argv[1],"-h")){
		printUsage();
		return 0;
	} else if(argc != 4){ //3 for the arguments + the 1 for the file name
		fprintf(stderr,"Error: incorrect # of args");
		printUsage();
		return 1;
	}

	//these will fail for us if there's a problem with the args
	numLoops = getInt(argv[1], GN_GT_0, "num-loops");
	numThreads = getInt(argv[2], GN_GT_0, "num-threads");
	char * concurrencyMethod = argv[3];

	if(streq(concurrencyMethod,"none")){
		incrementer_func = &increment_with_no_lock;
	} else if(streq(concurrencyMethod,"mutex")){
		incrementer_func = &increment_with_mutex;
		init_mutex();
	} else if(streq(concurrencyMethod,"spinlock")){
		incrementer_func = &increment_with_spinlock;
		init_spinlock();
	} else if(streq(concurrencyMethod,"readwritelock")){
		incrementer_func = &increment_with_readwritelock;
		init_readwritelock();
	} else if(streq(concurrencyMethod,"signalwait")){
		incrementer_func = &increment_with_signalwait;
		init_signalwait();
	} else if(streq(concurrencyMethod,"semaphore")){
		incrementer_func = &increment_with_semaphore;
		init_semaphore();
	} else {
		fprintf(stderr,"Error: invalid or unknown concurrency mechanism given (%s)",concurrencyMethod);
		return 1;
	}


	pthread_t* threads = malloc(sizeof(pthread_t) * numThreads);
	if(threads == NULL){
		fprintf(stderr,"Error: could not allocate memory for %d threads.",numThreads);
		return 1;
	}

	clock_gettime(CLOCK_REALTIME, &spec);
	unsigned long int startTime_ms = spec.tv_nsec/1000000ul + spec.tv_sec*1000ul;

	int i;

	//create all of the threads at once
	for(i = 0 ; i < numThreads ; i++){
		threadStatus = pthread_create(threads + i, NULL, incrementer_func, &numLoops);
		if(threadStatus != 0)
			errExitEN(threadStatus, "pthread_create");
	}

	clock_gettime(CLOCK_REALTIME, &spec);
	unsigned long int allCreatedTime_ms = spec.tv_nsec/1000000ul + spec.tv_sec*1000ul;

	//join to all of the threads.
	//I don't join right after creating, to ensure that the threads all start and run concurrently
	for(i = 0 ; i < numThreads ; i++){
		threadStatus = pthread_join(threads[i], NULL);
		if(threadStatus != 0)
			errExitEN(threadStatus, "pthread_join");
	}

	clock_gettime(CLOCK_REALTIME, &spec);
	unsigned long int allFinishedTime_ms = spec.tv_nsec/1000000ul + spec.tv_sec*1000ul;

	printf("glob = %d\n", glob);
	printf("Time to create threads:\t%7lu ms\n",(allCreatedTime_ms-startTime_ms));
	printf("Time to run:\t\t%7lu ms\n",(allFinishedTime_ms-startTime_ms));
	exit(EXIT_SUCCESS);
}
