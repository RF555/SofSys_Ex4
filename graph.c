#include "graph.h"

graph *init_graph(int n) {
    p_graph g = (graph *) malloc(sizeof(graph));
    if (g == NULL) {
        printf("MEMORY ALLOCATION ERROR\n");
        return NULL;
    }
    for (int i = 0; i < n; ++i) {
        p_node curr_n = gen_node(i);
        if (i == 0) {
            g->n_root = curr_n;
            g->n_tail = curr_n;
        } else {
            p_node temp_n = g->n_tail;
            curr_n->prev_n = temp_n;
            temp_n->next_n = curr_n;
            g->n_tail = curr_n;
        }
    }
    g->node_size = n;
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
        } else { curr_r = curr_r->prev_n; }
    }
    return NULL;
}

int add_node(graph *g, int id, edge_list *new_e_list) {
    if (g->node_size == 0) {
        p_node n = gen_node(id);
        g->n_root = n;
        g->n_tail = n;
        g->node_size = 1;
        n->out_edges = new_e_list;
        g->edge_size += new_e_list->size;
        return 1;
    }
    p_node exist_n = search_n(g, id);
    if (exist_n == NULL) {
        free(exist_n);
        exist_n=NULL;
        p_node new_n = gen_node(id);
        new_n->out_edges = new_e_list;
        g->edge_size += new_e_list->size;
        p_node temp_n = g->n_tail;
        new_n->prev_n = temp_n;
        temp_n->next_n = new_n;
        g->n_tail = new_n;
        g->node_size += 1;
        return 1;
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
        if (new_e_list->size == 0) {
            return 1;
        } else {
            update_in_edges(g, new_e_list);
        }
    }
    return 1;
}

int update_in_edges(graph *g, edge_list *new_e_list) {
    p_edge curr_e = new_e_list->e_root;
    int og_e_size = g->edge_size;
    while (curr_e != NULL) {
        p_node dest_n = search_n(g, curr_e->dest);
        if (dest_n == NULL) {
            printf("ERROR!\n");
            free(dest_n);
            dest_n=NULL;
            return 0;
        }
        push_edge(dest_n->in_edges, curr_e);
        g->edge_size += 1;
        curr_e = curr_e->next_e;
    }
    if (og_e_size == g->edge_size) {
        return 1;
    } else {
        printf("ERROR!\n");
        return 0;
    }
}

int add_Edge(graph *g, edge *e) {
    p_node src_n = search_n(g, e->src);
    if (src_n == NULL) {
        printf("ERROR- SRC NODE DOESN'T EXISTS!\n");
        free(src_n);
        src_n=NULL;
        free(e);
        e=NULL;
        return 0;
    }
    p_node dest_n = search_n(g, e->dest);
    if (dest_n == NULL) {
        printf("ERROR- DEST NODE DOESN'T EXISTS!\n");
        free(dest_n);
        dest_n=NULL;
        free(e);
        e=NULL;
        return 0;
    }
    push_edge(src_n->out_edges, e);
    push_edge(dest_n->in_edges, e);
    g->edge_size += 1;
    return 1;
}


