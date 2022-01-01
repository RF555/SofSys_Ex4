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
