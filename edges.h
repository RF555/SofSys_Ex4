#ifndef _EDGES_H
#define _EDGES_H

#include <stdio.h>
#include <stdlib.h>

typedef struct Edge {
    int src;
    float w;
    int dest;
} edge, *p_edge;

typedef struct EdgeArr {
    edge *e_arr;
    size_t used;
    size_t size;
} edge_arr;

void init_edge_arr(edge_arr *arr, int init_size);

void add_edge(edge_arr *arr, int src, float w, int dest);


void remove_edge(edge_arr *arr, edge e);

void free_edge_arr(edge_arr *arr);


#endif //_EDGES_H
