//#include <stdio.h>
#include "algo.h"

int test_edges() {
    p_edge e01_p = gen_edge(0, 1, 1);
    print_e(e01_p);
    p_edge e10_p = gen_edge(1, 1, 0);
    print_e(e10_p);
    p_edge e12_p = gen_edge(1, 1, 2);
    print_e(e12_p);
    p_edge e21_p = gen_edge(2, 1, 1);
    print_e(e21_p);
    p_edge e23_p = gen_edge(2, 1, 3);
    print_e(e23_p);
    p_edge e32_p = gen_edge(3, 1, 2);
    print_e(e32_p);
    printf("\n");
    // List
    p_e_list pe = init_edge_list();
    print_e_list(pe);
    // PUSH
    push_edge(pe, e01_p);
    print_e_list(pe);
    push_edge(pe, e10_p);
    print_e_list(pe);
    push_edge(pe, e12_p);
    print_e_list(pe);
    push_edge(pe, e21_p);
    print_e_list(pe);
    push_edge(pe, e23_p);
    print_e_list(pe);
    push_edge(pe, e32_p);
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
/*
    free_edge_list(pe);
    print_e_list(pe);
    return 0;
*/
}

int test_nodes() {
    p_node n0 = gen_node(0);
    print_node(n0);
    p_node n1 = gen_node(1);
    print_node(n1);
    p_node n2 = gen_node(2);
    print_node(n2);
    p_node n3 = gen_node(3);
    print_node(n3);
    // ADD EDGES
    push_Edge(n0->out_edges, 0, 1, 1);
    push_Edge(n1->in_edges, 0, 1, 1);
    push_Edge(n1->out_edges, 1, 1, 0);
    push_Edge(n0->in_edges, 1, 1, 0);
    push_Edge(n1->out_edges, 1, 1, 2);
    push_Edge(n2->in_edges, 1, 1, 2);
    push_Edge(n2->out_edges, 2, 1, 1);
    push_Edge(n1->in_edges, 2, 1, 1);
    push_Edge(n2->out_edges, 2, 1, 3);
    push_Edge(n3->in_edges, 2, 1, 3);
    push_Edge(n3->out_edges, 3, 1, 2);
    push_Edge(n2->in_edges, 3, 1, 2);
    printf("\n");
    print_node(n0);
    print_node(n1);
    print_node(n2);
    print_node(n3);
    printf("\n");
    //FREE NODE
    printf("is n0 free? %d", free_n(n0));
}

int test_graph() {
    p_graph g= init_graph(4);
    printf("init_graph:\n");
    print_graph(g);
    //ADD EDGE
    add_edge(g,0,1,1);
    printf("add_edge 0->1:\n");
    print_graph(g);
    add_edge(g,1,1,0);
    printf("add_edge 1->0:\n");
    print_graph(g);
    add_edge(g,1,1,2);
    printf("add_edge 1->2:\n");
    print_graph(g);
    add_edge(g,2,1,1);
    printf("add_edge 2->1:\n");
    print_graph(g);
    add_edge(g,2,1,3);
    printf("add_edge 2->3:\n");
    print_graph(g);
    add_edge(g,3,1,2);
    printf("add_edge 3->2:\n");
    print_graph(g);
    //ADD NODE
    printf("add_node: 4\n");
    add_node(g,4,NULL);
    print_graph(g);
}

int main() {
    printf("Hello, World!\n");
//    test_edges();
//    test_nodes();
    test_graph();

    return 0;
}
