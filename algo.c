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

int is_latter(char ch) {
    if (ch >= A_ASCII && ch <= Z_ASCII || ch >= a_ASCII && ch <= z_ASCII) {
        return 0;
    } else { return 1; }
}

int seq_size(char *input) {
    int count = 1;
    while (is_latter(input[count])) {
        ++count;
    }
    return count;
}

