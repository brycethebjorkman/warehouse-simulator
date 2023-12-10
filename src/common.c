#ifndef COMMON_C
#define COMMON_C

#include "common.h"

int parse_input_csv(const char* filename, InputQueue* out) {
    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        return 1;
    }

    // maximum size record would be like "18446744073709551615,18446744073709551615,[18446744073709551615,...]"
    // so 21 + 21 + 1 + 21 * 52 = 1135 characters
    char line[2048];
    memset(line, '\0', sizeof(line));

    char str[2048];
    memset(str, '\0', sizeof(str));

    char s[2048];
    memset(s, '\0', sizeof(s));

    // parse CSV line by line
    while (fgets(line, sizeof(line), file) != NULL) {
        size_t first_comma = 0;
        size_t second_comma = 0;
        size_t open_bracket = 0;
        size_t close_bracket = 0;
        for (size_t i = 0; line[i] != '\0'; ++i) {
            char c = line[i];
            if (c == ',' && !first_comma) {
                first_comma = i;
            } else if (c == ',' && !second_comma) {
                second_comma = i;
            } else if (c == '[' ) {
                open_bracket = i;
            } else if (c == ']' ) {
                close_bracket = i;
            }
        }
        InputNode* next_node = malloc(sizeof(InputNode));

        strncpy(str, line, first_comma);
        next_node->input.time = strtoumax(str, NULL, 10);
        memset(str, '\0', sizeof(str));

        strncpy(str, line + first_comma + 1, second_comma);
        next_node->input.gate = strtoumax(str, NULL, 10);
        memset(str, '\0', sizeof(str));

        strncpy(str, line + open_bracket + 1, close_bracket);
        str[close_bracket] = ',';
        size_t start = 0;
        for (size_t j = 0; j < strlen(str); ++j) {
            if (str[j] == ',') {
                strncpy(s, str + start, j);
                next_node->input.pallets[next_node->input.num_pallets] = strtoumax(str, NULL, 10);
                next_node->input.num_pallets++;
                memset(s, '\0', sizeof(s));
                start = j + 1;
            }
        }
        SLIST_INSERT_HEAD(&out->head, next_node, next);
    }

    fclose(file);

    return 0;
}

#endif
