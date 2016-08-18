LIBS =
CC = g++
CFLAGS = -O3 -Wall -std=c++11

all: variadic_templ array_size

variadic_templ:
	$(CC) $(CFLAGS) $@.cpp $(LIBS) -o $@

array_size:
	$(CC) $(CFLAGS) $@.cpp $(LIBS) -o $@

clean:
	-rm -f *.o
	-rm -f variadic_templ array_size
