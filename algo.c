#include "algo.h"

char *get_input() {
    char *input = (char *) malloc(INIT_LEN * sizeof(char));
    int len = INIT_LEN;
    int count = 0;
    char ch;
    scanf("%c", &ch);
    while (ch != END_OF_INPUT) {
        if (count + ADD_LEN >= len) {
            input = realloc(input, (len += INIT_LEN) * sizeof(char));
        }
        input[count++] = ch;
        scanf("%c", &ch);
    }
    input[count] = '\0';
    return input;
}

int is_cmd(char ch) {
    if (ch == A_ASCII || ch == a_ASCII || ch == B_ASCII || ch == b_ASCII || ch == D_ASCII
        || ch == d_ASCII || ch == S_ASCII || ch == s_ASCII || ch == T_ASCII || ch == t_ASCII) {
        return 1;
    } else { return 0; }
}

int seq_end(char *input) {
    int end = 1;
    while (!is_cmd(input[end]) && input[end] != END_OF_INPUT) {
        ++end;
    }
    return end;
}

int A(graph *g, char *input, int end) {
    free_graph(g);
    int curr_ch = 2;
    char *ptr1;
    int init_n = (int) strtol(input+curr_ch, &ptr1, 10);
    int diff1 = (int) (ptr1 - (input+curr_ch));
    curr_ch += diff1;
    g = init_graph(init_n);
    ++curr_ch;
    p_node curr_n;
    while (curr_ch < end) {
        if (curr_ch == end) {
            break;
        } else if (input[curr_ch] == 'n') {
            ++curr_ch;
            char *ptr;
            int src_id = (int) strtol(input+curr_ch, &ptr, 10);
            int diff = (int) (ptr - (input+curr_ch));
            curr_ch += diff;
            curr_n = search_n(g, src_id);
            ++curr_ch;
        } else if (input[curr_ch] == ' ') {
            ++curr_ch;
        } else {
            char *ptr;
            int dest_id = (int) strtol(input+curr_ch, &ptr, 10);
            int diff = (int) (ptr - (input+curr_ch));
            curr_ch += diff;
            int w = (int) strtol(input+curr_ch, &ptr, 10);
            int diff2 = (int) (ptr - (input+curr_ch));
            curr_ch += diff2;
            add_edge(g, curr_n->id, w, dest_id);
            ++curr_ch;
        }
    }
    return 0;
}




