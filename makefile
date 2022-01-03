CC = gcc
FLAGS = -Wall -g
AR = ar
OBJECT_LIB_NODES = nodes.o
OBJECT_LIB_EDGES = edges.o
OBJECT_LIB_GRAPH = graph.o
OBJECT_LIB_ALGO = algo.o
OBJECT_MAIN = main.o
MY_OBJECT_LIBS = edges.o nodes.o graph.o algo.o
MY_DYNAMIC_LIB = dylib.so


all: graph

# DYNAMIC linking
graph: $(OBJECT_MAIN) $(MY_DYNAMIC_LIB)
	$(CC) $(FLAGS) -o graph $(OBJECT_MAIN) ./$(MY_DYNAMIC_LIB) -lm

# DYNAMIC library
$(MY_DYNAMIC_LIB): $(MY_OBJECT_LIBS)
	$(CC) -shared -o $(MY_DYNAMIC_LIB) $(MY_OBJECT_LIBS)

$(OBJECT_LIB_ALGO): algo.c algo.h
	$(CC) $(FLAGS) -c algo.c

$(OBJECT_LIB_GRAPH): graph.c graph.h
	$(CC) $(FLAGS) -c graph.c

$(OBJECT_LIB_NODES): nodes.c nodes.h
		$(CC) $(FLAGS) -c nodes.c

$(OBJECT_LIB_EDGES): edges.c edges.h
	$(CC) $(FLAGS) -c edges.c

$(OBJECT_MAIN): main.c algo.h
	$(CC) $(FLAGS) -c main.c

.PHONY: clean all

clean:
	rm -f *.o *.so graph