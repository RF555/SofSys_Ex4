#ifndef ALGO_H
#define ALGO_H

#include "graph.h"

#define INIT_LEN 10
#define ADD_LEN 2
#define END_OF_INPUT '\n'
#define PARSE_CH '0'
#define A_ASCII 65
#define B_ASCII 66
#define D_ASCII 68
#define S_ASCII 83
#define T_ASCII 84
#define a_ASCII 97
#define b_ASCII 98
#define d_ASCII 100
#define s_ASCII 115
#define t_ASCII 116

char *get_input();

int seq_end(char *input);

int A(graph *g, char *input, int end);

int B(graph *g, char *input, int end);

int D(graph *g, char *input, int end);

int Shortest_path(graph *g, char *input, int end);

int TSP(graph *g, char *input, int end);


#endif //ALGO_H
