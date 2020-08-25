CC = clang++-9
FLAGS = -Wall -g

all: prefix_table prefix_table_opt

prefix_table: prefix_table.o 
	$(CC) $(FLAGS) -o prefix_table prefix_table.o 

prefix_table.o: prefix_table.cpp prefix_table.hpp
	$(CC) $(FLAGS) -c prefix_table.cpp


prefix_table_opt: prefix_table_opt.o 
	$(CC) $(FLAGS) -o prefix_table_opt prefix_table_opt.o 

prefix_table_opt.o: prefix_table_opt.cpp prefix_table.hpp
	$(CC) $(FLAGS) -c prefix_table_opt.cpp



.PHONY: clean all

clean:
	rm -f *.o prefix_table prefix_table_opt
