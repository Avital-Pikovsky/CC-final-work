CC = clang++-9
FLAGS = -Wall -g

all: edf bd

edf: edf.o 
	$(CC) $(FLAGS) -o edf edf.o 

edf.o: edf.cpp
	$(CC) $(FLAGS) -c edf.cpp

bd: bd.o 
	$(CC) $(FLAGS) -o bd bd.o 

bd.o: bd.cpp
	$(CC) $(FLAGS) -c bd.cpp


.PHONY: clean all

clean:
	rm -f *.o edf bd
