#include "algo.h"

char *get_input() {
    char *input = (char *) malloc(INIT_LEN * sizeof(char));
    int len = INIT_LEN;
    int count = 0;
    char ch;
    scanf("%c", &ch);
    while (ch != END_OF_INPUT1) {
        if (count + ADD_LEN >= len) {
            input = realloc(input, (len += INIT_LEN) * sizeof(char));
        }
        input[count++] = ch;
        scanf("%c", &ch);
    }
    input[count] = END_OF_INPUT2;
    return input;
}

int is_cmd(char ch) {
    if (ch == A_ASCII || ch == a_ASCII || ch == B_ASCII || ch == b_ASCII || ch == D_ASCII
        || ch == d_ASCII || ch == S_ASCII || ch == s_ASCII || ch == T_ASCII || ch == t_ASCII) {
        return 1;
    } else { return 0; }
}

int seq_end(char *input) {
    int end = CMD;
    while (!is_cmd(input[end]) && input[end] != END_OF_INPUT1 && input[end] != END_OF_INPUT2) {
        ++end;
    }
    return end;
}

int A(graph *g, char *input, int end) {
    free_graph(g);
    int curr_ch = START;
    char *ptr;
    int init_n = (int) strtol(input + curr_ch, &ptr, 10);
    int diff = (int) (ptr - (input + curr_ch));
    curr_ch += diff;
    g = init_graph(init_n);
    ++curr_ch;
    p_node curr_n;
    while (curr_ch < end) {
        if (curr_ch == end) {
            break;
        } else if (input[curr_ch] == 'n') {
            ++curr_ch;
            int src_id = (int) strtol(input + curr_ch, &ptr, 10);
            diff = (int) (ptr - (input + curr_ch));
            curr_ch += diff;
            curr_n = search_n(g, src_id);
            ++curr_ch;
        } else if (input[curr_ch] == ' ') {
            ++curr_ch;
        } else {
            int dest_id = (int) strtol(input + curr_ch, &ptr, 10);
            diff = (int) (ptr - (input + curr_ch));
            curr_ch += diff;
            int w = (int) strtol(input + curr_ch, &ptr, 10);
            diff = (int) (ptr - (input + curr_ch));
            curr_ch += diff;
            add_edge(g, curr_n->id, w, dest_id);
            ++curr_ch;
        }
    }
    return 0;
}

int B(graph *g, char *input, int end) {
    int curr_ch = START;
    char *ptr;
    int new_id = (int) strtol(input + curr_ch, &ptr, 10);
    int diff = (int) (ptr - (input + curr_ch));
    curr_ch += diff;
    p_e_list new_e_list = init_edge_list();
    while (curr_ch < end) {
        if (curr_ch == end) {
            break;
        } else if (input[curr_ch] == ' ') {
            ++curr_ch;
        } else {
            int dest_id = (int) strtol(input + curr_ch, &ptr, 10);
            diff = (int) (ptr - (input + curr_ch));
            curr_ch += diff;
            int w = (int) strtol(input + curr_ch, &ptr, 10);
            diff = (int) (ptr - (input + curr_ch));
            curr_ch += diff;
            push_Edge(new_e_list, new_id, w, dest_id);
            ++curr_ch;
        }
    }
    add_node(g, new_id, new_e_list);
    return 0;
}

int D(graph *g, char *input, int end) {
    int curr_ch = START;
    char *ptr;
    int delete_id = (int) strtol(input + curr_ch, &ptr, 10);
//    int diff = (int) (ptr - (input + curr_ch));
//    curr_ch += diff;
    remove_node(g, delete_id);
    return 0;
}

p_edge search_e_by_dest(p_e_list out_list, int dest) {
    p_edge curr_e = out_list->e_root;
    while (curr_e != NULL) {
        if (curr_e->dest == dest) {
            return curr_e;
        } else {
            curr_e = curr_e->next_e;
        }
    }
    return NULL;
}

int dijkstra(p_graph g, p_node src_n) {
    int src_id = src_n->id;
    p_node curr_n = g->n_root;
    while (curr_n != NULL) {
        if (curr_n->id == src_id) {
            curr_n->curr_w = 0;
        } else {
            curr_n->curr_w = INT_MAX;
        }
        curr_n->tag = WHITE;
        curr_n = curr_n->next_n;
    }
    p_e_list q = init_edge_list();
    push_Edge(q, src_id, -1, -1);
    while (q->e_root != NULL) {
        int curr_id = q->e_root->src;
        curr_n = search_n(g, curr_id);
        pop_e_root(q);
        if (curr_n->tag == WHITE) {
            curr_n->tag = BLACK;
            p_edge curr_out_e = curr_n->out_edges->e_root;
            while (curr_out_e != NULL) {
                p_node curr_dest = search_n(g, curr_out_e->dest);
                if (curr_dest->tag == WHITE) {
                    p_edge temp_e = search_e_by_dest(curr_n->out_edges, curr_dest->id);
                    if (temp_e == NULL) {
                        printf("ERROR dijkstra- no such edge\n");
                        return 0;
                    } else if (curr_dest->curr_w > (src_n->curr_w + temp_e->w)) {
                        curr_dest->curr_w = (src_n->curr_w + temp_e->w);
                        p_edge e_ = curr_dest->out_edges->e_root;
                        while (e_ != NULL) {
                            push_Edge(q, curr_dest->id, -1, -1);
                            e_ = e_->next_e;
                        }
                    }
                }
                curr_out_e = curr_out_e->next_e;
            }
        }
    }
    free_edge_list(q);
    return 1;
}


int Shortest_path(graph *g, char *input, int end) {
    int curr_ch = START;
    char *ptr;
    int src_id = (int) strtol(input + curr_ch, &ptr, 10);
    int diff = (int) (ptr - (input + curr_ch));
    curr_ch += diff + 1;
    int dest_id = (int) strtol(input + curr_ch, &ptr, 10);
    diff = (int) (ptr - (input + curr_ch));
    curr_ch += diff;
    p_node src = search_n(g, src_id);
    p_node dest = search_n(g, dest_id);
    int path = -1;
    if (dest == NULL || src == NULL) {
        printf("Dijsktra shortest path: %d\n", path);
        return -1;
    } else {
        dijkstra(g, src);
        path = dest->curr_w;
        if (path == INT_MAX || path < 0) {
            printf("Dijsktra shortest path: %d\n", -1);
            return -1;
        } else {
            printf("Dijsktra shortest path: %d\n", path);
            return path;
        }
    }
}


int TSP(graph *g, char *input, int end) {
    return 0;
}








