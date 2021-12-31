#include "nodes.h"

node *gen_node(int id_) {
    p_node n = (node *) malloc(sizeof(node));
    if (n == NULL) {
        printf("MEMORY ALLOCATION ERROR\n");
        return NULL;
    }
    n->id = id_;
    n->in_edges = init_edge_list();
    n->out_edges = init_edge_list();
    n->next_n = NULL;
    n->prev_n = NULL;
    return n;
}

int free_n(node *n) {
    if (n->prev_n != NULL || n->next_n != NULL || n->out_edges->size > 0 || n->in_edges->size > 0) {
        printf("ERROR- please clear node before freeing it!\n");
        return 0;
    } else {
        free_edge_list(n->in_edges);
        free_edge_list(n->out_edges);
        free(n);
        n=NULL;
        return 1;
    }
}

