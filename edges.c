#include "edges.h"

enum comp {
//    same_pos = 1, diff_pos = 2, same_w = 4, w1 = 16, w2 = 32
    same_pos = 1, diff_pos = 0, same_w = 1, w1 = 0, w2 = 0
};

enum comp compare_pos(edge *e1, edge *e2) {
    if (e1->src == e2->src && e1->dest == e2->dest) { return same_pos; }
    else { return diff_pos; }
}

enum comp compare_w(edge *e1, edge *e2) {
    if (e1->w == e2->w) { return same_w; }
    else if (e1->w > e2->w) { return w1; }
//           e1->w < e2->w
    else { return w2; }
}

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
        if (compare_w(&arr->e_arr[i], &e) & compare_w(&arr->e_arr[i], &e)) {
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


int free_edge_list(edge_list *e_list){
    return 0;
}
