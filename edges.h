#ifndef _EDGES_H
#define _EDGES_H

#include <stdio.h>

typedef struct Edge {
    int src;
    float w;
    int dest;
} edge, *p_edge;

typedef struct EdgeArr {
    edge *arr;
    int used;
    int size;
} edge_arr;

int init_edge_arr(edge_arr *arr, int init_size);

int free_edge_arr(edge_arr *arr);


#endif //_EDGES_H
