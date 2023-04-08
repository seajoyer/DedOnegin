#include "alphabetic_sort.h"
#include "utf8_string_tools.h"
#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

char* string_reverse(char* string)
{
    // char string[] = "Mình nói tiếng Việt HelloПриветэ!";

    if (!string || !*string)
        return string;

    for (size_t pos_left = 0, pos_right = strlen(string) - 1;
         pos_left < pos_right; pos_left++, pos_right--) {

        char ch = string[pos_left];
        string[pos_left] = string[pos_right];
        string[pos_right] = ch;
    }

    for (size_t pos_left = 0, char_continuation_size = 0; pos_left < strlen(string); pos_left++) {
        if (utf8_is_continuation(string[pos_left])) {
            ++char_continuation_size;
            continue;
        }
        for (size_t shift = char_continuation_size; shift > char_continuation_size / 2; shift--) {
            char tmp_byte = string[pos_left - (char_continuation_size - shift)];
            string[pos_left - (char_continuation_size - shift)] = string[pos_left - shift];
            string[pos_left - shift] = tmp_byte;
        }
        char_continuation_size = 0;
    }
    return string;
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
    FILE* fp = fopen("res.txt", "w+");
    for (size_t i = 1; i < amount_of_lines; i++) {
        char current_line[max_line_len], tmp_string1[max_line_len], tmp_string2[max_line_len];

        size_t j = i - 1;

        // printf("\n\n%s\n%s\n\n", strrev(text_to_parse + j * max_line_len, tmp_string1), strrev(current_line, tmp_string2));

        printf("i = %zu\n", i);

        // printf("%s", string_reverse(text_to_parse + j * max_line_len, tmp_string1));
        // printf("%s\n\n", string_reverse(current_line, tmp_string2));

        // printf("%s", string_reverse(current_line, tmp_string1));

        // printf("%d\n", strcmp(string_reverse(text_to_parse + j * max_line_len, tmp_string1), string_reverse(current_line, tmp_string2)));

        // while (j >= 0 && strcmp(strrev(text_to_parse + j * max_line_len, tmp_string1), strrev(current_line, tmp_string2)) > 0) {
        //     strcpy(text_to_parse + (j + 1) * max_line_len, text_to_parse + j * max_line_len);
        //     --j;
        // }
        // strcpy(text_to_parse + (j + 1) * max_line_len, current_line);
        // printf("i = %zu\n", i);
    }
    fcloseall();
}
