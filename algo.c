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
    p_PQ pq = gen_PQ();
    push(pq, src_n);
    while (!is_empty(pq)) {
        curr_n = peeq(pq);
//        int curr_src_id = curr_n->id;
        int curr_src_w = curr_n->curr_w;
        pop(pq);
        if (curr_n->tag == WHITE) {
            curr_n->tag = BLACK;
            p_edge curr_out_e = curr_n->out_edges->e_root;
            while (curr_out_e != NULL) {
                int curr_e_w = curr_out_e->w;
                p_node curr_dest = search_n(g, curr_out_e->dest);
//                int curr_dest_id = curr_dest->id;
//                int curr_dest_w = curr_dest->curr_w;
                if (curr_dest->tag == WHITE) {
                    if (curr_dest->curr_w > (curr_src_w + curr_e_w)) {
                        curr_dest->curr_w = (curr_src_w + curr_e_w);
                        p_edge e_ = curr_n->out_edges->e_root;
                        while (e_ != NULL) {
                            p_node temp_n = search_n(g, e_->dest);
                            push(pq, temp_n);
                            e_ = e_->next_e;
                        }
                    }
                }
                curr_out_e = curr_out_e->next_e;
            }
        }
    }
    free_pq(pq);
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


// PQ implementation:

PQ *gen_PQ() {
    p_PQ new_PQ = (PQ *) malloc(sizeof(PQ));
    new_PQ->size = 0;
    new_PQ->root = NULL;
    return new_PQ;
}

n_pq *gen_pq_(node *n) {
    pq_p new_pq = (n_pq *) malloc(sizeof(n_pq));
    new_pq->node_ptr = n;
    new_pq->next = NULL;
    new_pq->visited=WHITE;
    return new_pq;
}

node *peeq(PQ *pq) {
    return pq->root->node_ptr;
}


int peeq_w_from_src(n_pq *npq) {
    return npq->node_ptr->curr_w;
}


int pop(PQ *pq) {
    if (!is_empty(pq)) {
        pq_p temp = pq->root;
        pq->root = temp->next;
        pq->size -= 1;
        if (pq->size == 0) {
            free(pq->root);
            pq->root = NULL;
        }
        free(temp);
        temp = NULL;
    }
    return 0;
}

int push(PQ *pq, p_node n) {
    pq_p new_pq = gen_pq_(n);
    if (is_empty(pq)) {
        pq->root = new_pq;
        pq->size = 1;
    } else if (peeq_w_from_src(pq->root) >= n->curr_w) {
        new_pq->next = pq->root;
        pq->root = new_pq;
        pq->size += 1;
    } else {
        pq_p temp_pq = pq->root;
        while (temp_pq->next != NULL && peeq_w_from_src(temp_pq->next) < n->curr_w) {
            temp_pq = temp_pq->next;
        }
        new_pq->next = temp_pq->next;
        temp_pq->next = new_pq;
        pq->size += 1;
    }
    return 0;
}

int is_empty(PQ *pq) {
    return (pq->size <= 0 && pq->root == NULL);
}

int free_pq(PQ *pq) {
    if (is_empty(pq)) {
        free(pq);
        pq = NULL;
        return 1;
    } else {
        printf("ERROR free_pq- pq is not empty!\n");
        return 0;
    }
}







