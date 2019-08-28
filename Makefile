CC = g++

CompileParms = -c -Wall -fPIC -O3

OBJS = main.cc

main: $(OBJS)
	$(CC) $(OBJS) -o main

clean: 
	rm -f main
