#include "edges.h"

enum comp {
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
}

edge *gen_edge(int src_, int w_, int dest_) {
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

int print_e(edge *e) {
    if (e == NULL) {
        printf("ERROR can't print- edge is NULL!\n");
    } else {
        printf("{ src: %d, w: %d, dest: %d }", e->src, e->w, e->dest);
    }
    return 0;
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
    if ((e == NULL && pe_list->size > 0) || e->prev_e != NULL || e->next_e != NULL) {
        printf("ERROR set_e_root- edge has siblings OR is empty and list is not!\n");
        return 0;
    } else {
        p_edge curr_r = (edge *) malloc(sizeof(edge));
        if (curr_r == NULL) {
            printf("MEMORY ALLOCATION ERROR\n");
            free(e);
            e = NULL;
            return 0;
        }
        curr_r = pe_list->e_root;
        e->next_e = curr_r;
        curr_r->prev_e = e;
        pe_list->e_root = e;
        free(curr_r);
        curr_r = NULL;
        pe_list->size += 1;
        return 1;
    }
}

int set_e_tail(p_e_list pe_list, edge *e) {
    if ((e == NULL && pe_list->size > 0) || e->prev_e != NULL || e->next_e != NULL) {
        printf("ERROR set_e_tail- edge has siblings OR is empty and list is not!\n");
        return 0;
    }
    p_edge curr_t = pe_list->e_tail;
    e->prev_e = curr_t;
    curr_t->next_e = e;
    pe_list->e_tail = e;
    pe_list->size += 1;
    return 1;
}

p_edge search_e(p_e_list pe_list, edge *e) {
    if (e == NULL) {
        printf("ERROR- edge is NULL!\n");
        return 0;
    }
    p_edge curr_e = pe_list->e_root;
    while (curr_e != NULL) {
        if (compare_pos(curr_e, e)) { return curr_e; }
        else { curr_e = curr_e->next_e; }
    }
    return NULL;
}

void push_edge(p_e_list pe_list, edge *e) {
    if (pe_list->size <= 0 && pe_list->e_root == NULL && pe_list->e_tail == NULL) {
        pe_list->e_root = e;
        pe_list->e_tail = e;
        pe_list->size = 1;
        return;
    } else {
        p_edge exist_e = search_e(pe_list, e);
        if (exist_e == NULL) {
            set_e_tail(pe_list, e);
            return;
        } else {
            exist_e->w = e->w;
            free(e);
            e = NULL;
        }
    }
}

void push_Edge(p_e_list pe_list, int src_, int w_, int dest_) {
    p_edge new_pe = gen_edge(src_, w_, dest_);
    push_edge(pe_list, new_pe);
}

int pop_e_root(p_e_list pe_list) {
    if (pe_list->size == 1) {
        p_edge temp = pe_list->e_root;
        pe_list->e_tail = NULL;
        pe_list->e_root = NULL;
        pe_list->size = 0;
        free(temp);
        temp = NULL;
        return 1;
    } else if (pe_list->size <= 0 || pe_list->e_root == NULL) { return 0; }
    else {
        p_edge temp_e = pe_list->e_root;
        pe_list->e_root = temp_e->next_e;
        pe_list->e_root->prev_e = NULL;
        free(temp_e);
        temp_e = NULL;
        pe_list->size -= 1;
        return 1;
    }
}

int pop_e_tail(p_e_list pe_list) {
    if (pe_list->size == 1) {
        p_edge temp = pe_list->e_tail;
        pe_list->e_tail = NULL;
        pe_list->e_root = NULL;
        pe_list->size = 0;
        free(temp);
        temp = NULL;
        return 1;
    } else if (pe_list->size <= 0 || pe_list->e_tail == NULL) { return 0; }
    else {
        p_edge temp_e = pe_list->e_tail;
        pe_list->e_tail = temp_e->prev_e;
        pe_list->e_tail->next_e = NULL;
        free(temp_e);
        temp_e = NULL;
        pe_list->size -= 1;
        return 1;
    }
}

int pop_e(p_e_list pe_list, edge *e_) {
    if (e_ == NULL || pe_list->size <= 0 || pe_list->e_root == NULL) { return 0; }
    else if (compare_pos(e_, pe_list->e_root)) {
        pop_e_root(pe_list);
        return 1;
    } else if (compare_pos(e_, pe_list->e_tail)) {
        pop_e_tail(pe_list);
        return 1;
    } else {

        p_edge temp_e = search_e(pe_list, e_);
        if (temp_e == NULL) { return 0; }
        else {
            p_edge temp_prev = temp_e->prev_e;
            p_edge temp_next = temp_e->next_e;
            temp_prev->next_e = temp_next;
            temp_next->prev_e = temp_prev;
            free(temp_e);
            temp_e = NULL;
            pe_list->size -= 1;
            return 1;
        }
    }
}

int free_edge_list(p_e_list pe_list) {
    if (pe_list == NULL || (pe_list->e_root == NULL && pe_list->e_tail == NULL)) {
        return 0;
    }
    while (pe_list->e_tail != NULL) {
        pop_e_root(pe_list);
    }
    if (pe_list->size > 0 || pe_list->e_tail != NULL || pe_list->e_root != NULL) {
        printf("ERROR- couldn't free the list!\n");
        return 0;
    } else {
        free(pe_list);
        pe_list = NULL;
        return 1;
    }
}

int print_e_list(edge_list *e_list) {
    printf("pe->size = %d, [ ", e_list->size);
    p_edge pe = e_list->e_root;
    while (pe != NULL) {
        print_e(pe);
        printf(", ");
        pe = pe->next_e;
    }
    printf(" ] *pe_list = %p\n", e_list);
    return 0;
}
