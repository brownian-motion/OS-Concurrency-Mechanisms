MAIN=main.c
EXE_NAME=hw5
NUM_LOOPS=100000
SMALL_THREAD_NUM=5
LARGE_THREAD_NUM=50

all: clean build

build: $(MAIN)
	gcc $(MAIN) -o $(EXE_NAME) -lpthread -lrt

clean:
	$(RM) $(EXE_NAME)
	$(RM) run.log

test: clean build
	touch run.log
	make test-all-few-threads > run.log
	make test-all-many-threads >> run.log

test-all-few-threads:
	./$(EXE_NAME) $(NUM_LOOPS) $(SMALL_THREAD_NUM) none
	./$(EXE_NAME) $(NUM_LOOPS) $(SMALL_THREAD_NUM) semaphore
	./$(EXE_NAME) $(NUM_LOOPS) $(SMALL_THREAD_NUM) mutex
	./$(EXE_NAME) $(NUM_LOOPS) $(SMALL_THREAD_NUM) spinlock
	./$(EXE_NAME) $(NUM_LOOPS) $(SMALL_THREAD_NUM) readwritelock
	./$(EXE_NAME) $(NUM_LOOPS) $(SMALL_THREAD_NUM) signalwait

test-all-many-threads:
	./$(EXE_NAME) $(NUM_LOOPS) $(LARGE_THREAD_NUM) none
	./$(EXE_NAME) $(NUM_LOOPS) $(LARGE_THREAD_NUM) semaphore
	./$(EXE_NAME) $(NUM_LOOPS) $(LARGE_THREAD_NUM) mutex
	./$(EXE_NAME) $(NUM_LOOPS) $(LARGE_THREAD_NUM) spinlock
	./$(EXE_NAME) $(NUM_LOOPS) $(LARGE_THREAD_NUM) readwritelock
	./$(EXE_NAME) $(NUM_LOOPS) $(LARGE_THREAD_NUM) signalwait