#ifndef ALGO_H
#define ALGO_H

#include "graph.h"

#define INIT_LEN 10
#define ADD_LEN 2
#define END_OF_INPUT '\n'
#define A_ASCII 65
#define Z_ASCII 90
#define a_ASCII 97
#define z_ASCII 122

char *get_input();

int seq_end(char *input);

void A(graph *g, char *input, int end);

void B(graph *g, char *input, int end);

void D(graph *g, char *input, int end);

float Shortest_path(graph *g, char *input, int end);

void TSP(graph *g, char *input, int end);


#endif //ALGO_H
