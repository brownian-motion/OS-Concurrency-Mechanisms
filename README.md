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
 * [get_num.h](http://man7.org/tlpi/code/online/book/lib/get_num.h.html) and [.c](http://man7.org/tlpi/code/online/book/lib/get_num.c.html) for parsing numbers, used by `tlpi_hdr.h`
 * [error_functions.h](http://man7.org/tlpi/code/online/book/lib/error_functions.h.html) and [.c](http://man7.org/tlpi/code/online/book/lib/error_functions.c.html) for reporting errors in command-line arguments, used by `tlpi_hdr.h`
  * [ename.c.inc](http://man7.org/tlpi/code/online/book/lib/ename.c.inc.html), a set of enums used by `error_functions.h`

## Concurrency Methods
This program tests several methods of protecting shared resources in concurrent systems.
Each are outlined below.

### None
The data is not guarded through any particular means; any thread may read or write the data at any time.
#### Pros
This is extremely fast, and eliminates overhead due to locking mechanisms.
#### Cons
This is inherently prone to race conditions that can affect the result of computations using a shared resource.
#### Best use case
This works best when "stale" data is not a bad thing - that is, when multiple threads are just reading or dealing with data that doesn't need to be very precise.

### Mutex
The data is guarded by locking a mutex before the critical incrementing section, and then unlocking it at the end of incrementation.
#### Pros
Very, very fast. Simple, and easy to use.
#### Cons
If many mutexes are used, deadlock can occur between threads waiting on eachother's locked mutexes before they can unlock their own.
#### Best use case
Mutexes work best in low-level operations, where there is a predefined order of claiming and releasing these locks.

### Spin lock
Each thread busywaits until its lock is available, then locks, increments, and unlocks.
#### Pros
Simple, and easy to use.
#### Cons
Dreadfully slow, since each thread is busywaiting on its quantum (active time) while it waits for the lock.
####Best use case
Efficient when there are very few threads, but *terrible* for many threads. It would also work well in multiprocessor systems, because a busywaiting thread could immediately resume when a thread on different processor releases the lock, rather than wait until its woken up again.

### Read-Write Lock
Each thread repeatedly tries to obtain a lock for writing to a global variable, increments that variable, unlocks, and repeats until its job is done.
#### Pros
This lets other threads read concurrently as long as there is no thread trying to write, which removes some unnecessary blocking.
#### Cons
The added complexity makes it slower than simpler methods.
#### Best use case
This is best when many threads will need to read cocnurrently, but very few threads will need to write to a shared resource.

### Signal/Wait
Each thread waits until another thread signals that it is totally done, and then increments the global variable several times.
#### Pros
It's pretty fast, and makes efficient use of the time each thread is given.
#### Cons
It requires an additional mutex, which could possibly restrict its usefulness in the same way that mutexes need to be acquired in order.
#### Best use case
This is best when there a *lot* of threads running concurrently.

### Semaphore
Decrements a semaphore counter using `sem_wait` on each loop to wait for a lock, increments the global counter, then increments the semaphore counter using `sem_post` to release the lock.
#### Pros
Very simple, and effective for low-level operations.
#### Cons
Slower than mutexes when many threads are involved, and often harder to use. Similarly to mutexes, using multiple without a predifined order could result in deadlock.
#### Best use case
It's best used for very low-level operations where every thread that uses the semaphore is inside the same library. For example, code controlling circular buffers could use a semaphore to control it very quickly.

## Bugs
* I couldn't figure out any sort of reasonable condition for signal/wait to check every loop, so it only waits once per thread and performs every loop for that thread at once. As such it's uncharacteristically fast compared to the others.

## Contributing
Currently, no contributions will be accepted to this project. You are welcome to fork it and use the code for your own purposes under the MIT License, provided that no part of this code is used for any similar academic project. As outlined under the MIT License, any work copied from this repository must be properly and explicitly attributed.
