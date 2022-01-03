#include "graph.h"

graph *init_graph(int n) {
    p_graph g = (graph *) malloc(sizeof(graph));
    if (g == NULL) {
        printf("MEMORY ALLOCATION ERROR\n");
        return NULL;
    } else if (n == 0) {
        g->n_tail = NULL;
        g->n_root = NULL;
    } else {
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
    }
    g->node_size = n;
    g->edge_size = 0;
    return g;
}

p_node search_n(p_graph g, int id) {
    p_node curr = g->n_root;
    while (curr != NULL) {
        if (curr->id == id) {
            return curr;
        } else {
            curr = curr->next_n;
        }
    }
    return NULL;
}

int add_new_node(graph *g, int id) {
    if (g->node_size == 0) {
        p_node n = gen_node(id);
        g->n_root = n;
        g->n_tail = n;
        g->node_size = 1;
    } else {
        p_node n = gen_node(id);
        p_node temp = g->n_tail;
        temp->next_n = n;
        n->prev_n = temp;
        g->n_tail = n;
    }
    return 1;
}


int add_node(graph *g, int id, edge_list *new_e_list) {
    if (g->node_size == 0) {
        p_node n = gen_node(id);
        g->n_root = n;
        g->n_tail = n;
        g->node_size = 1;
        if (new_e_list != NULL) {
            n->out_edges = new_e_list;
            g->edge_size += new_e_list->size;
            update_in_edges(g, new_e_list);
        }
        return 1;
    } else {
        p_node exist_n = search_n(g, id);
        if (exist_n == NULL) {
            free(exist_n);
            exist_n = NULL;
            p_node new_n = gen_node(id);
            if (new_e_list != NULL) {
                new_n->out_edges = new_e_list;
                g->edge_size += new_e_list->size;
                update_in_edges(g, new_e_list);
            }
            p_node temp_n = g->n_tail;
            new_n->prev_n = temp_n;
            temp_n->next_n = new_n;
            g->n_tail = new_n;
            g->node_size += 1;
            return 1;
        } else {
            p_edge ex_out = exist_n->out_edges->e_root;
            while (ex_out != NULL) {
                p_node curr_n = search_n(g, ex_out->dest);
                if (curr_n == NULL) {
                    printf("ERROR- NODE DOESN'T EXISTS!\n");
                    return 0;
                } else {
                    pop_e(curr_n->in_edges, ex_out);
                    g->edge_size -= 1;
                }
                ex_out = ex_out->next_e;
            }
            free_edge_list(exist_n->out_edges);
            if (new_e_list == NULL) {
                free_edge_list(new_e_list);
                exist_n->out_edges = init_edge_list();
            } else {
                exist_n->out_edges = new_e_list;
                g->edge_size += new_e_list->size;
                update_in_edges(g, new_e_list);
            }
        }
        return 1;
    }
}

int update_in_edges(graph *g, edge_list *new_e_list) {
    p_edge curr_e = new_e_list->e_root;
    int src_id = curr_e->src;
    while (curr_e != NULL && src_id == curr_e->src) {
        p_node dest_n = search_n(g, curr_e->dest);
        //dest node doesn't exist- CREATE or ERROR???
        /* if (dest_n == NULL) {//ERROR
            printf("ERROR update_in_edges- dest node doesn't exist!\n");
            free(dest_n);
            dest_n = NULL;
            return 0;
        }*/
        if (dest_n == NULL) { // node doesn't exist? -> CREATE it
            add_new_node(g, curr_e->dest);
            free(dest_n);
        } else {
            push_Edge(dest_n->in_edges, src_id, curr_e->w, curr_e->dest);
            curr_e = curr_e->next_e;
        }
    }
/*    p_edge curr_e = new_e_list->e_root;
    int og_e_size = g->edge_size;
    while (curr_e != NULL) {
        p_node dest_n = search_n(g, curr_e->dest);
        if (dest_n == NULL) {
            printf("ERROR update_in_edges- dest node doesn't exist!\n");
            free(dest_n);
            dest_n = NULL;
            return 0;
        }
        push_edge(dest_n->in_edges, curr_e);
        g->edge_size += 1;
        curr_e = curr_e->next_e;
    }
    if (og_e_size == g->edge_size) {
        return 1;
    } else {
        printf("ERROR update_in_edges- comparison !\n");
        return 0;
    }
*/
    return 0;
}

int add_edge(graph *g, int src, int w, int dest) {
    p_edge e = gen_edge(src, w, dest);
    add_Edge(g, e);
    return 1;
}

int add_Edge(graph *g, edge *e) {
    p_node src_n = search_n(g, e->src);
    if (src_n == NULL) {
        printf("ERROR- SRC NODE DOESN'T EXISTS!\n");
        free(src_n);
        src_n = NULL;
        free(e);
        e = NULL;
        return 0;
    } else {
        p_node dest_n = search_n(g, e->dest);
        if (dest_n == NULL) {
            printf("ERROR- DEST NODE DOESN'T EXISTS!\n");
            free(dest_n);
            dest_n = NULL;
            free(e);
            e = NULL;
            return 0;
        } else {
            push_Edge(src_n->out_edges, e->src, e->w, e->dest);
            push_Edge(dest_n->in_edges, e->src, e->w, e->dest);
            free(e);
            e = NULL;
            g->edge_size += 1;
            return 1;
        }
    }
}

int remove_edge(graph *g, int src, int dest) {
    p_node src_n = search_n(g, src);
    if (src_n == NULL) {
        printf("ERROR remove_edge- SRC NODE DOESN'T EXISTS!\n");
        free(src_n);
        src_n = NULL;
        return 0;
    }
    p_node dest_n = search_n(g, dest);
    if (dest_n == NULL) {
        printf("ERROR remove_edge- DEST NODE DOESN'T EXISTS!\n");
        free(dest_n);
        dest_n = NULL;
        return 0;
    }
    p_edge e = gen_edge(src, 0, dest);
    pop_e(src_n->out_edges, e);
    pop_e(dest_n->in_edges, e);
    g->edge_size -= 1;
    free(e);
    e = NULL;
    return 1;
}

int remove_node(graph *g, int id) {
    p_node n = search_n(g, id);
    if (n == NULL) { //no node with that id
        return 0;
    }
    p_edge in_curr = n->in_edges->e_root;
    while (in_curr != NULL) {
        p_edge temp = in_curr->next_e;
        remove_edge(g, in_curr->src, in_curr->dest);
        in_curr = temp;
    }
    p_edge out_curr = n->out_edges->e_root;
    while (out_curr != NULL) {
        p_edge temp = out_curr->next_e;
        remove_edge(g, out_curr->src, out_curr->dest);
        out_curr = temp;
    }
    if (n->id == g->n_root->id && n->id == g->n_tail->id) {
        g->n_tail = NULL;
        g->n_root = NULL;
    } else if (n->id == g->n_root->id) {
        p_node temp = n->next_n;
        n->next_n = NULL;
        temp->prev_n = NULL;
        g->n_root = temp;
    } else if (n->id == g->n_tail->id) {
        p_node temp = n->prev_n;
        n->prev_n = NULL;
        temp->next_n = NULL;
        g->n_tail = temp;
    } else {
        p_node temp_perv = n->prev_n;
        p_node temp_next = n->next_n;
        n->next_n = NULL;
        n->prev_n = NULL;
        temp_next->prev_n = temp_perv;
        temp_perv->next_n = temp_next;
    }
    g->node_size -= 1;
    free_n_edges(n);
    free_n(n);
    return 1;
}

int free_graph(graph *g) {
    if (g->n_root == NULL && g->n_tail == NULL && g->edge_size == 0 && g->node_size == 0) {
        free(g);
        return 0;
    }
    p_node curr_n = g->n_root;
    while (curr_n != NULL) {
        p_node temp = curr_n->next_n;
        remove_node(g, curr_n->id);
        curr_n = temp;
    }
    if (g->node_size == 0 && g->edge_size == 0 && g->n_root == NULL && g->n_tail == NULL) {
        free(g);
        return 1;
    } else {
        printf("ERROR free_graph!");
        return 0;
    }
}


int print_graph(p_graph g) {
    printf("[ node_size: %d, edge_size: %d,\n", g->node_size, g->edge_size);
    p_node temp_n = g->n_root;
    while (temp_n != NULL) {
        print_node(temp_n);
        printf(",\n");
        temp_n = temp_n->next_n;
    }
    printf("]\n");
    return 0;
}
