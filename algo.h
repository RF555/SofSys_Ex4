#ifndef ALGO_H
#define ALGO_H

#include "graph.h"
#include "limits.h"

#define INIT_LEN 10
#define ADD_LEN 2
#define END_OF_INPUT1 '\n'
#define END_OF_INPUT2 '\0'
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
#define CMD 1
#define START 2


typedef struct PQ_N {
    p_node node_ptr;
    struct PQ_N *next;
    enum Tag visited;
} n_pq, *pq_p;

typedef struct PQ_ {
    int size;
    n_pq *root;

} PQ, *p_PQ;
PQ *gen_PQ();
n_pq *gen_pq_(node *n);
node *peeq(PQ *pq);
int peeq_w_from_src(n_pq *npq);
int pop(PQ *pq);
int push(PQ *pq, p_node n);
int is_empty(PQ *pq);
int free_pq(PQ *pq);

char *get_input();

int seq_end(char *input);

int A(graph *g, char *input, int end);

int B(graph *g, char *input, int end);

int D(graph *g, char *input, int end);

int Shortest_path(graph *g, char *input, int end);

int TSP(graph *g, char *input, int end);


#endif //ALGO_H
