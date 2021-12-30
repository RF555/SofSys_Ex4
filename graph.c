#include "graph.h"

graph *init_graph() {
    p_graph g = (graph *) malloc(sizeof(graph));
    if (g == NULL) {
        printf("MEMORY ALLOCATION ERROR\n");
        return NULL;
    }
    g->n_root = NULL;
    g->n_tail = NULL;
    g->node_size = 0;
    g->edge_size = 0;
    return g;
}

p_node search_n(p_graph g, int id) {
    p_node curr_l = g->n_root;
    p_node curr_r = g->n_tail;
    while (curr_r->id != curr_l->id) {
        if (curr_l->id == id) {
            return curr_l;
        } else {
            curr_l = curr_l->next_n;
        }
        if (curr_r->id == id) {
            return curr_r;
        } else {
            curr_r = curr_r->prev_n;
        }
    }
    return NULL;
}

int add_node(graph *g, int id, edge_list *pe_list) {
    if (g->node_size == 0) {
        p_node n = gen_node(id);
        g->n_root = n;
        g->n_tail = n;
        g->node_size = 1;
        return 1;
    }
    p_node exist_n = search_n(g, id);
    if (exist_n == NULL) {
        printf("ERROR- NODE ALREADY EXISTS!\n");
        free(exist_n);
        return 0;
    } else {
        while (exist_n->out_edges->e_root != NULL) {
            p_edge ex_out = exist_n->out_edges->e_root;
            p_node curr_n = search_n(g, ex_out->dest);
            if (curr_n == NULL) {
                printf("ERROR- NODE DOESN'T EXISTS!\n");
                return 0;
            } else {
                pop_e(curr_n->in_edges, ex_out);
            }
            pop_e_root(exist_n->out_edges);
            g->edge_size -= 1;
        }
        p_edge curr_new_e = pe_list->e_root;
        while (curr_new_e != NULL) {

        }

    }
}

int add_Edge(graph *g, edge *e) {
    p_node src_n= search_n(g,e->src);
    if(src_n==NULL){
        printf("ERROR- SRC NODE DOESN'T EXISTS!\n");
        free(src_n);
        return 0;
    }
    p_node dest_n= search_n(g,e->dest);
    if(dest_n==NULL){
        printf("ERROR- DEST NODE DOESN'T EXISTS!\n");
        free(dest_n);
        return 0;
    }
    push_edge(src_n->out_edges,e);
}















