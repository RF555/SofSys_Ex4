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

int D(graph *g, char *input, int end){
    int curr_ch = START;
    char *ptr;
    int delete_id = (int) strtol(input + curr_ch, &ptr, 10);
//    int diff = (int) (ptr - (input + curr_ch));
//    curr_ch += diff;
    remove_node(g,delete_id);
    return 0;
}




int Shortest_path(graph *g, char *input, int end){
    return 0;
}

int TSP(graph *g, char *input, int end){
    return 0;
}








