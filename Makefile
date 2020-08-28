CC = g++

CompileParms = -c -Wall -fPIC -O3

OBJS = \
	libs/agendaitem.o \
	main.o


HEADERS = \
	libs/agendaitem.h 

main: $(OBJS)
	$(CC) $(OBJS) -o main

libs/%.o:		%.cc $(HEADERS)
		$(COMPILE) -c $<

clean: 
	rm -f main
	rm -f $(OBJS)
