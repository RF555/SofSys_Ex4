//#include <stdio.h>
#include "algo.h"

int test_edges(){
    p_edge e01_p=gen_edge(0,1,1);
    print_e(e01_p);
    p_edge e10_p=gen_edge(1,1,0);
    print_e(e10_p);
    p_edge e12_p=gen_edge(1,1,2);
    print_e(e12_p);
    p_edge e21_p=gen_edge(2,1,1);
    print_e(e21_p);
    p_edge e23_p=gen_edge(2,1,3);
    print_e(e23_p);
    p_edge e32_p=gen_edge(3,1,2);
    print_e(e32_p);
    printf("\n");
    // List
    p_e_list  pe=init_edge_list();
    print_e_list(pe);
    // PUSH
    push_edge(pe,e01_p);
    print_e_list(pe);
    push_edge(pe,e10_p);
    print_e_list(pe);
    push_edge(pe,e12_p);
    print_e_list(pe);
    push_edge(pe,e21_p);
    print_e_list(pe);
    push_edge(pe,e23_p);
    print_e_list(pe);
    push_edge(pe,e32_p);
    print_e_list(pe);
    printf("\n");
    //POP_TAIL
/*
    pop_e_tail(pe);
    print_e_list(pe);
    pop_e_tail(pe);
    print_e_list(pe);
    pop_e_tail(pe);
    print_e_list(pe);
    pop_e_tail(pe);
    print_e_list(pe);
    pop_e_tail(pe);
    print_e_list(pe);
    pop_e_tail(pe);
    print_e_list(pe);
*/
    //POP_ROOT
/*
    pop_e_root(pe);
    print_e_list(pe);
    pop_e_root(pe);
    print_e_list(pe);
    pop_e_root(pe);
    print_e_list(pe);
    pop_e_root(pe);
    print_e_list(pe);
    pop_e_root(pe);
    print_e_list(pe);
    pop_e_root(pe);
    print_e_list(pe);
    pop_e_root(pe);
    print_e_list(pe);
*/
    //POP_E
/*
    pop_e(pe,e21_p);
    print_e_list(pe);
    pop_e(pe,e23_p);
    print_e_list(pe);
    pop_e(pe,e10_p);
    print_e_list(pe);
    pop_e(pe,e32_p);
    print_e_list(pe);
    pop_e(pe,e01_p);
    print_e_list(pe);
    pop_e(pe,e12_p);
    print_e_list(pe);
    pop_e(pe,e12_p);
    print_e_list(pe);
*/
    //FREE_LIST
    free_edge_list(pe);
    print_e_list(pe);
    return 0;
}


int main() {
    printf("Hello, World!\n");
    test_edges();



    return 0;
}
