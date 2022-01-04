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
            curr_n->curr_w = MAX;
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
                        if (curr_src_w == MAX || curr_e_w == MAX) {
                            curr_dest->curr_w = MAX;
                        } else {
                            curr_dest->curr_w = (curr_src_w + curr_e_w);
                        }
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
        if (path == MAX || path < 0) {
            printf("Dijsktra shortest path: %d\n", -1);
            return -1;
        } else {
            printf("Dijsktra shortest path: %d\n", path);
            return path;
        }
    }
}

int shortest_path(graph *g, p_node src, p_node dest) {
    dijkstra(g, src);
    return dest->curr_w;
}

//Cities *init_cities() {
//    p_cities cities = (Cities *) malloc(sizeof(Cities));
//    if (cities == NULL) {
//        printf("MEMORY ALLOCATION ERROR\n");
//        return NULL;
//    }
//    cities->A_n=NULL;
//    cities->B_n=NULL;
//    cities->C_n=NULL;
//    cities->D_n=NULL;
//    cities->E_n=NULL;
//    cities->F_n=NULL;
//    cities->G_n=NULL;
//    cities->curr_size=AA;
//}
//
//int add_city(Cities *c, p_node n){
//    switch (c->curr_size) {
//        case AA:
//            c->A_n=n;
//            c->A_visited=WHITE;
//            c->curr_size+=1;
//        case BB:
//            c->B_n=n;
//            c->curr_size+=1;
//        case CC:
//            c->C_n=n;
//            c->curr_size+=1;
//        case DD:
//            c->D_n=n;
//            c->curr_size+=1;
//        case EE:
//            c->E_n=n;
//            c->curr_size+=1;
//        case FF:
//            c->F_n=n;
//            c->curr_size+=1;
//        case GG:
//            c->G_n=n;
//            c->curr_size+=1;
//    }
//}



int tsp(p_graph g, p_PQ cities) {
    int min_dist = MAX;
    p_PQ copy_ = copy(cities);
    pq_p curr_start = cities->root;
    while (curr_start != NULL) {
        int start_id=curr_start->node_ptr->id;
        pq_p init = cities->root;
        while (init != NULL) {
            init->node_ptr->city_visit = GREY;
            init = init->next;
        }
        p_PQ pq = gen_PQ();
        pq_p curr_end = copy_->root;
        int end_id=curr_end->node_ptr->id;
        while (curr_end != NULL) {
            if (curr_start->node_ptr->id != curr_end->node_ptr->id) {
                push_dijkstra(pq, g, curr_end->node_ptr, curr_start->node_ptr);
            }
            curr_end = curr_end->next;
        }
        int sum = 0;
        p_node temp_curr = curr_start->node_ptr;
        int temp_id=temp_curr->id;
        while (!is_empty(pq)) {
            int pq_root_id= peeq(pq)->id;
            dijkstra(g, temp_curr);
            if (sum < MAX || peeq_w_from_src(pq->root) < MAX) {
                sum += peeq_w_from_src(pq->root);
            }else{
                sum=MAX;
            }
            pop(pq);
        }
        if (sum < min_dist) {
            min_dist = sum;
        }
        curr_start = curr_start->next;
    }
    return min_dist;
}


int TT(graph *g, char *input, int end) {
    int curr_ch = START;
    char *ptr;
    int k = (int) strtol(input + curr_ch, &ptr, 10);
    int diff = (int) (ptr - (input + curr_ch));
    curr_ch += diff;
    p_PQ cities = gen_PQ();
    while (curr_ch < end) {
        if (curr_ch == end) {
            break;
        } else if (input[curr_ch] == ' ') {
            ++curr_ch;
        } else {
            int curr_id = (int) strtol(input + curr_ch, &ptr, 10);
            diff = (int) (ptr - (input + curr_ch));
            curr_ch += diff;
            p_node curr_n = search_n(g, curr_id);
            if (curr_n != NULL) {
                curr_n->city = GREY;
                push(cities, curr_n);
            }
            ++curr_ch;
        }
    }
    int dist = tsp(g, cities);
    if (dist >= MAX) {
        printf("TSP shortest path: %d\n", -1);
    } else {
        printf("TSP shortest path: %d\n", dist);
    }
    return dist;
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

int push_dijkstra(PQ *pq, p_graph g, p_node new_n, p_node src_n) {
//    dijkstra(g, src_n);
    pq_p new_pq = gen_pq_(new_n);
    if (is_empty(pq)) {
        pq->root = new_pq;
        pq->size = 1;
    } else {
//        if (peeq_w_from_src(pq->root) >= new_n->curr_w) {
        if (shortest_path(g, src_n, pq->root->node_ptr) >= shortest_path(g, src_n, new_n)) {
            new_pq->next = pq->root;
            pq->root = new_pq;
            pq->size += 1;
        } else {
            pq_p temp_pq = pq->root;
            while (temp_pq->next != NULL && peeq_w_from_src(temp_pq->next) < new_n->curr_w) {
                temp_pq = temp_pq->next;
            }
            new_pq->next = temp_pq->next;
            temp_pq->next = new_pq;
            pq->size += 1;
        }
    }
    return 0;
}


int is_empty(PQ *pq) {
    return (pq->size <= 0 && pq->root == NULL);
}

PQ *copy(p_PQ pq) {
    p_PQ copy = gen_PQ();
    pq_p curr = pq->root;
    while (curr != NULL) {
        push(copy, curr->node_ptr);
        curr = curr->next;
    }
    return copy;
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







