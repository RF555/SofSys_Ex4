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

edge *gen_edge(edge *e, int src, float w, int dest);

typedef struct EdgeList {
    edge *e_root;
    edge *e_tail;
    int size;
} edge_list, *p_e_list;

int init_edge_list(edge_list *e_list);

int set_e_root(edge *e);

int set_e_tail(edge *e);

int add_edge(edge_list *e_list, int src, float w, int dest);

int remove_edge(edge_list *e_list, edge e);

int free_edge_list(edge_list *e_list);

#endif //_EDGES_H
