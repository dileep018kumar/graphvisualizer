CFLAGS=`pkg-config libgvc --cflags` -Wall -g -O2
LDFLAGS=`pkg-config libgvc --libs` -L/usr/local/lib
LDLIBS=-lgvc -lcgraph
all: simple dot demo

simple: simple.o

dot: dot.o

demo: demo.o

clean:
	rm -rf simple dot demo*.o

