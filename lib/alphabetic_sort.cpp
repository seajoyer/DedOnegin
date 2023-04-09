#include "alphabetic_sort.h"
#include "utf8_string_tools.h"
#include <assert.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <wctype.h>

void clear_string_beginning(char* buffer, char* string, size_t line_length)
{
    wchar_t wbuffer[line_length];
    mbstowcs(wbuffer, string, line_length);

    if (!iswalpha(wbuffer[0])) {
        for (size_t i = 1, j = 0, empty_string = 1; i < line_length; i++) {
            if (!iswalpha(wbuffer[i]) && empty_string)
                continue;
            else
                empty_string = 0;

            wbuffer[j] = wbuffer[i];
            wbuffer[i] = ' ';
            ++j;
        }
    }

    wcstombs(buffer, wbuffer, line_length);
}

void sort_by_line_beginnings(size_t amount_of_lines, size_t max_line_len, char* text_to_parse)
{
    for (size_t i = 1; i < amount_of_lines; i++) {
        char current_line[max_line_len];
        strcpy(current_line, text_to_parse + i * max_line_len);

        char current_line_preprocessed[max_line_len];
        clear_string_beginning(current_line_preprocessed, current_line, max_line_len);

        char previous_line_preprocessed[max_line_len];
        size_t j = i - 1;
        clear_string_beginning(previous_line_preprocessed, text_to_parse + j * max_line_len, max_line_len);

        while (j < max_line_len && strcmp(previous_line_preprocessed, current_line_preprocessed) > 0) {
            strcpy(text_to_parse + (j + 1) * max_line_len, text_to_parse + j * max_line_len);
            --j;
            clear_string_beginning(previous_line_preprocessed, text_to_parse + j * max_line_len, max_line_len);
        }
        strcpy(text_to_parse + (j + 1) * max_line_len, current_line);
    }
}

void sort_by_line_ends(size_t amount_of_lines, size_t max_line_len, char* text_to_parse)
{
    for (size_t i = 1; i < amount_of_lines; i++) {
        char current_line[max_line_len];
        strcpy(current_line, text_to_parse + i * max_line_len);

        char current_line_preprocessed[max_line_len];
        strcpy(current_line_preprocessed, current_line);
        string_reverse(current_line_preprocessed);
        clear_string_beginning(current_line_preprocessed, current_line_preprocessed, max_line_len);

        size_t j = i - 1;
        char previous_line_preprocessed[max_line_len];
        strcpy(previous_line_preprocessed, text_to_parse + j * max_line_len);
        string_reverse(previous_line_preprocessed);
        clear_string_beginning(previous_line_preprocessed, previous_line_preprocessed, max_line_len);

        while (j < max_line_len && strcmp(previous_line_preprocessed, current_line_preprocessed) > 0) {
            strcpy(text_to_parse + (j + 1) * max_line_len, text_to_parse + j * max_line_len);
            --j;
            strcpy(previous_line_preprocessed, text_to_parse + j * max_line_len);
            string_reverse(previous_line_preprocessed);
            clear_string_beginning(previous_line_preprocessed, previous_line_preprocessed, max_line_len);
        }
        strcpy(text_to_parse + (j + 1) * max_line_len, current_line);
    }
}
