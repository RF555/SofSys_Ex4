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
    n->tag = WHITE;
    return n;
}

int free_n_edges(node *n) {
    free_edge_list(n->in_edges);
    free_edge_list(n->out_edges);
    return 0;
}


int free_n(node *n) {
    if (n->prev_n != NULL || n->next_n != NULL) {
        printf("ERROR- please clear node before freeing it!\n");
        return 0;
    } else {
        free_edge_list(n->in_edges);
        free_edge_list(n->out_edges);
        free(n);
        return 1;
    }
}

int print_node(node *n) {
    if (n->next_n == NULL && n->prev_n == NULL) {
        printf("{ id: %d, in_edges->size: %d, out_edges->size: %d, prev_n: NULL, next_n: NULL }",
               n->id, n->in_edges->size, n->out_edges->size);
        return 0;
    } else if (n->next_n == NULL) {
        printf("{ id: %d, in_edges->size: %d, out_edges->size: %d, prev_n: %d, next_n: NULL }",
               n->id, n->in_edges->size, n->out_edges->size, n->prev_n->id);
        return 0;
    } else if (n->prev_n == NULL) {
        printf("{ id: %d, in_edges->size: %d, out_edges->size: %d, prev_n: NULL, next_n: %d }",
               n->id, n->in_edges->size, n->out_edges->size, n->next_n->id);
        return 0;
    } else {
        printf("{ id: %d, in_edges->size: %d, out_edges->size: %d, prev_n: %d, next_n: %d }",
               n->id, n->in_edges->size, n->out_edges->size, n->prev_n->id, n->next_n->id);
        return 1;
    }

}

