#ifndef _EDGES_H
#define _EDGES_H

#include <stdio.h>
#include <stdlib.h>

typedef struct Edge {
    int src;
    float w;
    int dest;
    struct Edge *prev_e;
    struct Edge *next_e;
} edge, *p_edge;

edge *gen_edge(int src_, float w_, int dest_);

int set_prev_e(edge *e, edge *prev_e_);

int set_next_e(edge *e, edge *next_e_);


typedef struct EdgeList {
    edge *e_root;
    edge *e_tail;
    int size;
} edge_list, *p_e_list;

p_e_list init_edge_list();
int set_e_root(p_e_list pe_list, edge *e);
int set_e_tail(p_e_list pe_list, edge *e);
p_edge search_e(p_e_list pe_list, edge *e);
int push_edge(p_e_list pe_list, int src_, float w_, int dest_);
void pop_e_root(p_e_list pe_list);
void pop_e_tail(p_e_list pe_list);
void pop_e(p_e_list pe_list, edge *e_);
int free_edge_list(p_e_list pe_list);

#endif //_EDGES_H
