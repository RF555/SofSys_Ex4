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
#define MAX 2*((INT_MAX)/3)
//typedef enum TAKEN{AA,BB,CC,DD,EE,FF,GG}taken;
//
//typedef struct CITIES{
//    p_node A_n;
//    Tag A_visited;
//    p_node B_n;
//    Tag B_visited;
//    p_node C_n;
//    Tag C_visited;
//    p_node D_n;
//    Tag D_visited;
//    p_node E_n;
//    Tag E_visited;
//    p_node F_n;
//    Tag F_visited;
//    p_node G_n;
//    Tag G_visited;
//    taken curr_size;
//}Cities, *p_cities;
//
//Cities *init_cities();
//int add_city(Cities *c,p_node n);



typedef struct PQ_N {
    p_node node_ptr;
    struct PQ_N *next;
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
int push_dijkstra(PQ *pq,p_graph g, p_node new_n, p_node src_n);
int is_empty(PQ *pq);
PQ *copy(p_PQ pq);
//int update(p_PQ pq);
int free_pq(PQ *pq);

char *get_input();

int seq_end(char *input);

int A(graph *g, char *input, int end);

int B(graph *g, char *input, int end);

int D(graph *g, char *input, int end);

int Shortest_path(graph *g, char *input, int end);

int TT(graph *g, char *input, int end);


#endif //ALGO_H
