MAIN=main.c
EXE_NAME=hw5


all: clean build

build: $(MAIN)
	gcc $(MAIN) include/*.c -o $(EXE_NAME) -lpthread -lrt

clean:
	$(RM) $(EXE_NAME)