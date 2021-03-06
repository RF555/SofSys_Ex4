#ifndef _EDGES_H
#define _EDGES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Edge {
    int src;
    int w;
    int dest;
    struct Edge *prev_e;
    struct Edge *next_e;
} edge, *p_edge;

edge *gen_edge(int src_, int w_, int dest_);

int print_e(edge *e);

typedef struct EdgeList {
    edge *e_root;
    edge *e_tail;
    int size;
} edge_list, *p_e_list;

p_e_list init_edge_list();

int set_e_root(p_e_list pe_list, edge *e);

int set_e_tail(p_e_list pe_list, edge *e);

p_edge search_e(p_e_list pe_list, edge *e);

void push_edge(p_e_list pe_list, edge *e);

void push_Edge(p_e_list pe_list, int src_, int w_, int dest_);

int pop_e_root(p_e_list pe_list);

int pop_e_tail(p_e_list pe_list);

int pop_e(p_e_list pe_list, edge *e_);

int free_edge_list(p_e_list pe_list);

int print_e_list(edge_list *e_list);

#endif //_EDGES_H
