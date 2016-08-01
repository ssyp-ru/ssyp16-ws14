CC=gcc
CFLAGS=-Wall -std=c99 -Wno-unused-function -g
LFLAGS=-lm

main: main.c geometry.o imageWork.o modelWork.o graphicalLibrary.o matrix.o
	$(CC) main.c geometry.o imageWork.o modelWork.o graphicalLibrary.o matrix.o $(CFLAGS) $(LFLAGS) -o main 

geometry.o: geometry.c geometry.h
	$(CC) $(CFLAGS) -c geometry.c

imageWork.o: imageWork.c imageWork.h
	$(CC) $(CFLAGS) -c imageWork.c

modelWork.o: modelWork.c modelWork.h
	$(CC) $(CFLAGS) -c modelWork.c

graphicalLibrary.o: graphicalLibrary.c graphicalLibrary.h
	$(CC) $(CFLAGS) -c graphicalLibrary.c

matrix.o: matrix.c matrix.h
	$(CC) $(CFLAGS) -c matrix.c

clean:
	rm main *.o

rebuild: clean main

run: main
	./main

