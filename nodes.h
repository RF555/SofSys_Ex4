#ifndef _NODES_H
#define _NODES_H

#include "edges.h"

enum Tag {
    WHITE, GREY, BLACK
};

typedef struct Node {
    int id;
    p_e_list in_edges;
    p_e_list out_edges;
    struct Node *prev_n;
    struct Node *next_n;
    enum Tag tag;
} node, *p_node;

node *gen_node(int id_);

int free_n_edges(node *n);

int free_n(node *n);

int print_node();
/*
typedef struct NodesList {
    node *n_arr;
    size_t size;
//    size_t used;
} node_list, *p_n_list;

int init_node_list(node_list *n_list, int init_size);

int set_n_root(node *n);

int set_n_tail(node *n);

int add_node(node_list *n_list, int id);

int remove_node(node_list *n_list, int id);

int free_node_list(node_list *n_list);

*/
#endif //_NODES_H
