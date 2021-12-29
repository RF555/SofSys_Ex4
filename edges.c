#include "edges.h"

#define DIFF 0
#define DIFF_W 1
#define SAME 2

int compare_edge(edge *e1, edge *e2) {
    if (e1->src == e2->src && e1->w == e2->w &&){
//        TO COMPLETE!!!
    }
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


void remove_edge(edge_arr *arr, edge e) {
    for (int i = 0; i < arr->used; ++i) {
        if (compare_edge(&arr->e_arr[i], &e) == SAME) {
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


void free_edge_arr(edge_arr *arr) {
    free(arr->e_arr);
    arr->e_arr = NULL;
    arr->used = 0;
    arr->size = 0;
}
