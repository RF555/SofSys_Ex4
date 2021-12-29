#ifndef _NODES_H
#define _NODES_H

//#include <stdio.h>
#include "edges.h"

enum tag {
    WHITE, GREY, BLACK
};

typedef struct Node {
    int id;
    edge_arr in_edges;
    edge_arr out_edges;
} node, *p_node;

typedef struct NodesArr {
    node *n_arr;
    size_t used;
    size_t size;
} node_arr;

int init_node_arr(node_arr *arr, int init_size);

int free_node_arr(node_arr *arr);


#endif //_NODES_H
