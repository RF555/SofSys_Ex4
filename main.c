#include <string.h>
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
    p_graph g = init_graph(4);
    printf("init_graph:\n");
    print_graph(g);
    //ADD EDGE
    add_edge(g, 0, 1, 1);
    printf("add_edge 0->1:\n");
    print_graph(g);
    add_edge(g, 1, 1, 0);
    printf("add_edge 1->0:\n");
    print_graph(g);
    add_edge(g, 1, 1, 2);
    printf("add_edge 1->2:\n");
    print_graph(g);
    add_edge(g, 2, 1, 1);
    printf("add_edge 2->1:\n");
    print_graph(g);
    add_edge(g, 2, 1, 3);
    printf("add_edge 2->3:\n");
    print_graph(g);
    add_edge(g, 3, 1, 2);
    printf("add_edge 3->2:\n");
    print_graph(g);
    //ADD NODE - new node that didn't exist and NO edges
/*
    printf("add_node: 4\n");
    add_node(g, 4, NULL);
    print_graph(g);
*/
    //ADD NODE - new node that didn't exist with edges
    p_e_list el_4 = init_edge_list();
    push_Edge(el_4, 4, 1, 3);
    push_Edge(el_4, 4, 1, 0);
    printf("add node 4 and edges 4->3 and 4->0:\n");
    add_node(g, 4, el_4);
    print_graph(g);
    //ADD NODE - new node that already exists (no edges)
    printf("add node 2 (no edges):\n");
    add_node(g, 2, NULL);
    print_graph(g);
    //ADD NODE - new node that already exists (with edges)
    p_e_list el_2 = init_edge_list();
    push_Edge(el_2, 2, 1, 1);
    push_Edge(el_2, 2, 1, 3);
    push_Edge(el_2, 2, 1, 4);
    printf("add node 2 (with edges):\n");
    add_node(g, 2, el_2);
    print_graph(g);
    //REMOVE EDGE
    printf("remove edge 2->4:\n");
    remove_edge(g, 2, 4);
    print_graph(g);
    //REMOVE NODE
    printf("remove node 2:\n");
    remove_node(g, 2);
    print_graph(g);
    //FREE GRAPH
    printf("free graph:\n");
    free_graph(g);
    print_graph(g);
}

int test_algo() {
    //INPUT
    char *input = get_input();
    printf("%s\n", input);
    printf("%lu\n", strlen(input));
    //SEQUENCE END
    int seq_size = seq_end(input);
    printf("seq_size=%d\n", seq_size);
    //A
    char *ptr;
//    printf("%ld\n", strtol(input,&ptr,10));
//    printf("%s",ptr);
    p_graph g = init_graph(0);
    A(g, input, seq_size);
    free(input);
    print_graph(g);
    //B
    input = get_input();
    int B_seq_size = seq_end(input);
    B(g, input, B_seq_size);
    print_graph(g);
    free(input);
    input = get_input();
    B_seq_size = seq_end(input);
    B(g, input, B_seq_size);
    print_graph(g);
    free(input);
    //D
    input = get_input();
    int D_seq_size = seq_end(input);
    D(g, input, D_seq_size);
    print_graph(g);
    free(input);

    return 0;
}

//int main() {
int main_test() {
    printf("Hello, World!\n");
//    test_edges();
//    test_nodes();
//    test_graph();
    test_algo();
}

///*
int main() {
//    main_test();
//    typedef enum Command {
//        AAA, BBB, DDD, SSS, TTT
//    } cmd;
    char *input = get_input();
    char *curr_seq = input;
    int curr_seq_size = 0;
    size_t full_size = strlen(input);
    p_graph g = init_graph(0);
    while (curr_seq[0] != END_OF_INPUT1 && curr_seq[0] != END_OF_INPUT2 && curr_seq[0] != input[full_size]) {
        curr_seq_size = seq_end(curr_seq);
        switch (curr_seq[0]) {
            case 'A':
                A(g, curr_seq, curr_seq_size);
                curr_seq = curr_seq + curr_seq_size;
                break;
            case 'B':
                B(g, curr_seq, curr_seq_size);
                curr_seq = curr_seq + curr_seq_size;

                break;
            case 'D':
                D(g, curr_seq, curr_seq_size);
                curr_seq = curr_seq + curr_seq_size;

                break;
            case 's':
                Shortest_path(g, curr_seq, curr_seq_size);
                curr_seq = curr_seq + curr_seq_size;

                break;
            case 'T':
                TSP(g, curr_seq, curr_seq_size);
                curr_seq = curr_seq + curr_seq_size;

                break;
        }
    }
    free(input);
    print_graph(g);
    return 0;
}
// */