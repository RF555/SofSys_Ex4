//
// Created by roeyf on 28/12/2021.
//

#ifndef SOFSYS_EX4_NODES_H
#define SOFSYS_EX4_NODES_H

//#include <stdio.h>
#include "edges.h"

enum tag {
    WHITE, GREY, BLACK
};

typedef struct Node {
    int id;
    edge_arr in_edges;
    edge_arr out_edges;
} node;

typedef struct NodesArr {
    node *arr;
    int used;
    int size;
} node_arr;

int init_node_arr(node_arr *arr, int init_size);

int add_node(node_arr *arr, node n);

int remove_node(node_arr *arr, node n);

int free_node_arr(node_arr *arr);


#endif //SOFSYS_EX4_NODES_H
