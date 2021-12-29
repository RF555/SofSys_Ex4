#ifndef SOFSYS_EX4_EDGES_H
#define SOFSYS_EX4_EDGES_H
#include <stdio.h>

typedef struct Edge {
    int src;
    float w;
    int dest;
} edge;

typedef struct EdgeArr {
    edge *arr;
    int used;
    int size;
} edge_arr;

int init_arr(edge_arr *arr, int init_size);
int add(edge_arr *arr, edge e);
int remove(edge_arr *arr, edge e);
int free_arr(edge_arr *arr);


#endif //SOFSYS_EX4_EDGES_H
