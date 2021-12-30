#ifndef _NODES_H
#define _NODES_H

//#include <stdio.h>
#include "edges.h"

enum tag {
    WHITE, GREY, BLACK
};

typedef struct Node {
    int id;
    edge_list in_edges;
    edge_list out_edges;
    struct Node *prev_n;
    struct Node *next_n;
} node, *p_node;

node *gen_node(node *n, int id);

typedef struct NodesArr {
    node *n_arr;
    size_t used;
    size_t size;
} node_list, *p_n_list;

int init_node_list(node_list *n_list, int init_size);

int set_n_root(node *n);

int set_n_tail(node *n);

int add_node(node_list *n_list, int id);

int remove_node(node_list *n_list, int id);

int free_node_list(node_list *n_list);


#endif //_NODES_H
