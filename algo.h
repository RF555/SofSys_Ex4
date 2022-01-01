#ifndef ALGO_H
#define ALGO_H

#include "graph.h"

#define INIT_LEN 10
#define ADD_LEN 2
#define END_OF_INPUT '\n'

char *get_input();

void A(graph *g, char *input);

void B(graph *g, char *input);

void D(graph *g, char *input);

float Shortest_path(graph *g, char *input);

void TSP(graph *g, char *input);


#endif //ALGO_H
