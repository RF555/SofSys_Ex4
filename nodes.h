#ifndef _NODES_H
#define _NODES_H

#include "edges.h"

typedef enum Tag {
    WHITE, GREY, BLACK
} Tag;

typedef struct Node {
    int id;
    p_e_list in_edges;
    p_e_list out_edges;
    struct Node *prev_n;
    struct Node *next_n;
    Tag tag;
    int curr_w;
    Tag city;
    Tag city_visit;
} node, *p_node;

node *gen_node(int id_);

int free_n_edges(node *n);

int free_n(node *n);

int print_node();

#endif //_NODES_H
