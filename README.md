# OS Concurrency Mechanisms
A project for a school assignment which compares the effectiveness of various concurrency mechanisms for using shared resources among threads.

## Specifications
This is a C program that accepts as parameters 1) how many times to increment a global variable in each thread, 2) how many threads to spawn, and 3) what type of concurrency mechanism to use for the shared counter.
This program targets Linux; it may work on other systems, but they are not supported.

### Execution

The executable should be run in two modes. 

        ./hw5 –h 
        ./hw5 <loops> <threads> <concurrency type>
The first prints out instructions of how to run the code to stderr. The second runs the code with the given parameters.

Options for the final parameter are discussed in more detail in [this section](#concurrency-methods).

### Compilation
Using a Makefile, compiling the code with `make all` should create an executable `hw5`.

### Dependencies
This code is derived from the [thread_inc.c](http://man7.org/tlpi/code/online/book/threads/thread_incr.c.html) script in the Linux Programming Interface book, and depends on the `pthread` library embedded in Linux, found [here](http://man7.org/tlpi/code/index.html), as well as the following individual files:

* [tlpi_hdr.h](http://man7.org/tlpi/code/online/book/lib/tlpi_hdr.h.html) for parsing command-line arguments
* [get_num.h](http://man7.org/tlpi/code/online/book/lib/get_num.h.html) for parsing numbers, used by `tlpi_hdr.h`
* [error_functions.h](http://man7.org/tlpi/code/online/book/lib/error_functions.h.html) for reporting errors in command-line arguments, used by `tlpi_hdr.h`

## Concurrency Methods
This program tests several methods of protecting shared resources in concurrent systems.
Each are outlined below.

### None
The data is not guarded through any particular means; any thread may read or write the data at any time.
#### Pros
This is extremely fast, and eliminates overhead due to locking mechanisms.
#### Cons
This is inherently prone to race conditions that can affect the result of computations using a shared resource.

### Mutex
#### Pros
#### Cons

### Spin lock
#### Pros
#### Cons

### Read-Write Lock
#### Pros
#### Cons

### Signal/Wait
#### Pros
#### Cons

### Semaphore
#### Pros
#### Cons

## Bugs
Any known bugs are listed below:

## Contributing
Currently, no contributions will be accepted to this project. You are welcome to fork it and use the code for your own purposes under the MIT License, provided that no part of this code is used for any similar academic project. As outlined under the MIT License, any work copied from this repository must be properly and explicitly attributed.
