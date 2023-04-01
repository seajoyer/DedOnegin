#include "alphabetic_sort.h"
#include <cctype>
#include <cstdio>
#include <string.h>

char* strrev(char* source_string, char* result_string)
{
    strcpy(result_string, source_string);
    if (!result_string || !*result_string)
        return result_string;

    for (size_t i = strlen(result_string) - 1, j = 0; i > j; i-- && j++) {
        char character = result_string[i];
        result_string[i] = result_string[j];
        result_string[j] = character;
    }
    return result_string;
}

void sort_by_line_beginnings(size_t amount_of_lines, size_t max_line_len, char* text_to_parse)
{
    for (size_t i = 1; i < amount_of_lines; i++) {
        char current_line[max_line_len];

        strcpy(current_line, text_to_parse + i * max_line_len);

        size_t j = i - 1;
        while (j >= 0 && strcmp(text_to_parse + j * max_line_len, current_line) > 0) {
            strcpy(text_to_parse + (j + 1) * max_line_len, text_to_parse + j * max_line_len);
            --j;
        }
        strcpy(text_to_parse + (j + 1) * max_line_len, current_line);
    }
}

void sort_by_line_ends(size_t amount_of_lines, size_t max_line_len, char* text_to_parse)
{
    for (size_t i = 1; i < amount_of_lines; i++) {
        char current_line[max_line_len], tmp_string1[max_line_len], tmp_string2[max_line_len];

        strcpy(current_line, text_to_parse + i * max_line_len);

        size_t j = i - 1;

        // printf("\n\n%s\n%s\n\n", strrev(text_to_parse + j * max_line_len, tmp_string1), strrev(current_line, tmp_string2));

        printf("i = %zu\n", i);

        printf("%d\n", strcmp(strrev(text_to_parse + j * max_line_len, tmp_string1), strrev(current_line, tmp_string2)));

        while (j >= 0 && strcmp(strrev(text_to_parse + j * max_line_len, tmp_string1), strrev(current_line, tmp_string2)) > 0) {
            strcpy(text_to_parse + (j + 1) * max_line_len, text_to_parse + j * max_line_len);
            --j;
        }
        strcpy(text_to_parse + (j + 1) * max_line_len, current_line);
    }
}
