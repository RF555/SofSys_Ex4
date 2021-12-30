#include "edges.h"

enum comp {
//    same_pos = 1, diff_pos = 2, same_w = 4, w1 = 16, w2 = 32
    same_pos = 1, diff_pos = 0, same_w = 1, w1 = 0, w2 = 0, same = 1, diff = 0
};

enum comp compare_pos(edge *e1, edge *e2) {
    if (e1->src == e2->src && e1->dest == e2->dest) { return same_pos; }
    else { return diff_pos; }
}

enum comp compare_w(edge *e1, edge *e2) {
    if (e1->w == e2->w) { return same_w; }
    else if (e1->w > e2->w) { return w1; }
    else /*e1->w < e2->w*/ { return w2; }
}

int compare_e(edge *e1, edge *e2) {
    return compare_pos(e1, e2) && compare_w(e1, e2);
//    return (compare_w(e1,e2) & compare_pos(e1,e2))==same;
}

edge *gen_edge(int src_, float w_, int dest_) {
    p_edge e = (edge *) malloc(sizeof(edge));
    if (e == NULL) {
        printf("MEMORY ALLOCATION ERROR\n");
        return NULL;
    }
    e->src = src_;
    e->w = w_;
    e->dest = dest_;
    e->next_e = NULL;
    e->prev_e = NULL;
    return e;
}

p_e_list init_edge_list() {
    p_e_list pe_list = (edge_list *) malloc(sizeof(edge_list));
    if (pe_list == NULL) {
        printf("MEMORY ALLOCATION ERROR\n");
        return NULL;
    }
    pe_list->size = 0;
    pe_list->e_root = NULL;
    pe_list->e_tail = NULL;
    return pe_list;
}

int set_e_root(p_e_list pe_list, edge *e) {
    if (e == NULL && pe_list->size > 0 || e->prev_e != NULL || e->next_e != NULL) {
        printf("ERROR\n");
        return 0;
    }
    p_edge curr_r = (edge *) malloc(sizeof(edge));
    if (curr_r == NULL) {
        printf("MEMORY ALLOCATION ERROR\n");
        return 0;
    }
    curr_r = pe_list->e_root;
    e->next_e = curr_r;
    curr_r->prev_e = e;
    pe_list->e_root = e;
    free(curr_r);
    pe_list->size += 1;
    return 1;
}

int set_e_tail(p_e_list pe_list, edge *e) {
    if (e == NULL && pe_list->size > 0 || e->prev_e != NULL || e->next_e != NULL) {
        printf("ERROR\n");
        return 0;
    }
    p_edge curr_t = (edge *) malloc(sizeof(edge));
    if (curr_t == NULL) {
        printf("MEMORY ALLOCATION ERROR\n");
        return 0;
    }
    curr_t = pe_list->e_tail;
    e->prev_e = curr_t;
    curr_t->next_e = e;
    pe_list->e_tail = e;
    free(curr_t);
    pe_list->size += 1;
    return 1;
}

p_edge search_e(p_e_list pe_list, edge *e) {
    if (e == NULL) {
        printf("ERROR\n");
        return 0;
    }
//    p_edge curr_l=(edge *) malloc(sizeof(edge));
//    if (curr_l == NULL) { printf("MEMORY ALLOCATION ERROR\n");return 0;}
    p_edge curr_l = pe_list->e_root;
//    p_edge curr_r=(edge *) malloc(sizeof(edge));
//    if (curr_r == NULL) { printf("MEMORY ALLOCATION ERROR\n");
//        free(curr_l);
//        return 0;}
    p_edge curr_r = pe_list->e_tail;
    while (!compare_e(curr_l, curr_r)) {
        if (compare_pos(e, curr_l)) {
//            free(curr_r);
            return curr_l; //don't forget to free curr_l later!
        } else {
            curr_l = curr_l->next_e;
        }
        if (compare_pos(e, curr_l)) {
//            free(curr_l);
            return curr_r; //don't forget to free curr_r later!
        } else {
            curr_r = curr_r->prev_e;
        }
    }
//    free(curr_l);
//    free(curr_r);
    return NULL;
}


int push_edge(p_e_list pe_list, int src_, float w_, int dest_) {
    p_edge new_pe = gen_edge(src_, w_, dest_);
    if (search_e(pe_list, new_pe)) {
        printf("ERROR- EDGE ALREADY EXISTS!\n");
        free(new_pe);
        return 0;
    } else {
        set_e_tail(pe_list, new_pe);
        return 1;
    }
}

int pop_e_root(p_e_list pe_list) {
    if (pe_list->size <= 0 || pe_list->e_root == NULL) { return 0; }
    p_edge temp_e = pe_list->e_root;
    pe_list->e_root = temp_e->next_e;
    pe_list->e_root->prev_e = NULL;
    free(temp_e);
    pe_list->size -= 1;
    return 1;
}

int pop_e_tail(p_e_list pe_list) {
    if (pe_list->size <= 0 || pe_list->e_tail == NULL) { return 0; }
    p_edge temp_e = pe_list->e_tail;
    pe_list->e_tail = temp_e->prev_e;
    pe_list->e_tail->next_e = NULL;
    free(temp_e);
    pe_list->size -= 1;
    return 1;
}

int pop_e(p_e_list pe_list, edge *e_) {
    if (e_ == NULL || pe_list->size <= 0 || pe_list->e_root == NULL) { return 0; }
    p_edge temp_e = search_e(pe_list, e_);
    if (temp_e == NULL) { return 0; }
    else {
        p_edge temp_prev = temp_e->prev_e;
        p_edge temp_next = temp_e->next_e;
        temp_prev->next_e = temp_next;
        temp_next->prev_e = temp_prev;
        free(temp_e);
        pe_list->size -= 1;
        return 1;
    }
}

int free_edge_list(p_e_list pe_list) {
    p_edge curr_e = pe_list->e_root;
    while (curr_e != NULL) {
        p_edge temp_e = curr_e;
        curr_e = curr_e->next_e;
        free(temp_e);
        pe_list->size -= 1;
    }
    if (pe_list->size > 0 || pe_list->e_tail != NULL || pe_list->e_root != NULL) {
        printf("ERROR- couldn't free the list!");
        return 0;
    } else {
        free(pe_list);
        return 1;
    }
}

/*
void init_edge_arr(edge_arr *arr, int init_size) {
    arr->e_arr = malloc(init_size * sizeof(edge));
    arr->used = 0;
    arr->size = init_size;
}

void add_edge(edge_arr *arr, int src, float w, int dest) {
    if (arr->used == arr->size) {
        arr->size *= 2;
        arr->e_arr = realloc(arr->e_arr, arr->size * sizeof(edge));
        if (arr->e_arr == NULL) { printf("error\n"); }
    }
    arr->e_arr[arr->used++].src = src;
    arr->e_arr[arr->used].w = w;
    arr->e_arr[arr->used].dest = dest;
}


int remove_edge(edge_list *arr, edge e) {
    for (int i = 0; i < arr->used; ++i) {
//        if (compare_edge(&arr->e_arr[i], &e) == SAME) {
        if (compare_w(&arr->e_arr[i], &e) & compare_pos(&arr->e_arr[i], &e)) {
            edge *temp_e = (edge *) malloc(sizeof(edge));
            if (temp_e == NULL) { printf("error\n"); }
            temp_e->src = arr->e_arr[arr->used].src;
            temp_e->w = arr->e_arr[arr->used].w;
            temp_e->dest = arr->e_arr[arr->used].dest;
            arr->e_arr[i].src = temp_e->src;
            arr->e_arr[i].w = temp_e->w;
            arr->e_arr[i].dest = temp_e->dest;
            arr->e_arr[arr->used].src = -1;
            arr->e_arr[arr->used].w = -1;
            arr->e_arr[arr->used].dest = -1;
            arr->used--;
            free(temp_e);
        }
    }
}

edge *gen_edge(edge *e, int src, float w, int dest) {
    return NULL;
}


int free_edge_list(edge_list *e_list) {
    return 0;
}
*/