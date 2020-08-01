CC = clang++-9
FLAGS = -Wall -g

all: congestion_control

congestion_control: congestion_control.o 
	$(CC) $(FLAGS) -o congestion_control congestion_control.o 

congestion_control.o: congestion_control.cpp
	$(CC) $(FLAGS) -c congestion_control.cpp

.PHONY: clean all

clean:
	rm -f *.o congestion_control
