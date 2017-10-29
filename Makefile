all: project

project: chess.c
	gcc chess.c -Wall -o chess
clean:
	rm *.o
