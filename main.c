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
#include "include/tlpi_hdr.h"

#include "incrementers/mutex_incrementer.c"
#include "incrementers/semaphore_incrementer.c"
#include "incrementers/spinlock_incrementer.c"
#include "incrementers/readwritelock_incrementer.c"
#include "incrementers/signalwait_incrementer.c"
#include "incrementers/bare_incrementer.c"

#define streq(s1, s2) (strcmp(s1, s2) == 0)

volatile int glob = 0;   /* "volatile" prevents compiler optimizations
                                   of arithmetic operations on 'glob' */

static void *(* incrementer_func)(void *) = 0; //what function each thread should use, to be set by main when parsing args

void printUsage(){
	printf("Usage: %s %s %s %s",argv[0],"<num-loops>","<num-threads>","<concurrency-method>");
	printf("Valid Concurrency methods are:\n\tnone\n\tmutex\n\tspinlock\n\treadwritelock\n\tsignalwait\n\tsemaphore");
}

int
main(int argc, char *argv[])
{
	pthread_t t1, t2;
	int numLoops, threadStatus, numThreads;

	if(argc == 2 && streq(argv[1],"-h")){
		printUsage();
		return 0;
	} else if(argc != 3){
		fprintf(stderr,"Error: incorrect # of args");
		printUsage();
		return 1;
	}

	//these will fail for us if there's a problem with the args
	numLoops = getInt(argv[1], GN_GT_0, "num-loops");
	numThreads = getInt(argv[2], GN_GT_0, "num-threads");
	char * concurrencyMethod = argv[3];

	if(streq(concurrencyMethod,"none")){
		thread_func = &increment_with_no_lock;
	} else if(streq(concurrencyMethod,"mutex")){
		thread_func = &increment_with_mutex;
		init_mutex();
	} else if(streq(concurrencyMethod,"spinlock")){
		thread_func = &increment_with_spinlock;
		init_spinlock();
	} else if(streq(concurrencyMethod,"readwritelock")){
		thread_func = &increment_with_readwritelock;
		init_readwritelock();
	} else if(streq(concurrencyMethod,"signalwait")){
		thread_func = &increment_with_signalwait;
		init_signalwait();
	} else if(streq(concurrencyMethod,"semaphore")){
		thread_func = &increment_with_semaphore;
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

	int startTime = time();

	for(int i = 0 ; i < numThreads ; i++){
		theadStatus = pthread_create(threads + i, NULL, incrementer_func, &numLoops);
		if(threadStatus != 0)
			errExitEn(threadStatus, "pthread_create");
	}

	int allCreatedTime = time();

	for(int i = 0 ; i < numThreads ; i++){
		threadStatus = pthread_join(threads[i], NULL);
		if(threadStatus != 0)
			errExitEn(threadStatus, "pthread_join");
	}

	int allFinishedTime = time();

	printf("glob = %d\n", glob);
	printf("Time to create threads:\t%.2f s",(allCreatedTime-startTime)/1000f);
	printf("Time to run:\t\t%.2f s",(allFinishedTime-startTime)/1000f);
	exit(EXIT_SUCCESS);
}