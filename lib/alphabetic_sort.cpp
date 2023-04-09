#include "alphabetic_sort.h"
#include "utf8_string_tools.h"
#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wctype.h>

void clear_string_beginning(char* string)
{
    size_t line_length = 1;
    while (string[line_length] != '\0')
        line_length++;

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
    wcstombs(string, wbuffer, line_length);
}

int strcmp_alphabetically_by_beginnings(void const* void_string1, void const* void_string2)
{
    char const* string1 = (char const*)void_string1;
    char const* string2 = (char const*)void_string2;

    size_t string_length = 1;
    for (int first_end_gained = 0, second_end_gained = 0; !(first_end_gained && second_end_gained); string_length++) {
        // printf("ch = %c\n", string1[string_length]);
        if (!first_end_gained && string1[string_length] == '\0')
            first_end_gained = 1;
        if (!second_end_gained && string2[string_length] == '\0')
            second_end_gained = 1;
    }

    char string1_preprocessed[string_length];
    strcpy(string1_preprocessed, string1);
    clear_string_beginning(string1_preprocessed);

    char string2_preprocessed[string_length];
    strcpy(string2_preprocessed, string2);
    clear_string_beginning(string2_preprocessed);

    return strcmp(string1_preprocessed, string2_preprocessed);
}

int strcmp_alphabetically_by_ends(void const* void_string1, void const* void_string2)
{
    char const* string1 = (char const*)void_string1;
    char const* string2 = (char const*)void_string2;

    size_t string_length = 1;
    for (int first_end_gained = 0, second_end_gained = 0; !(first_end_gained && second_end_gained); string_length++) {
        // printf("ch = %c\n", string1[string_length]);
        if (!first_end_gained && string1[string_length] == '\0')
            first_end_gained = 1;
        if (!second_end_gained && string2[string_length] == '\0')
            second_end_gained = 1;
    }

    char string1_preprocessed[string_length];
    strcpy(string1_preprocessed, string1);
    string_reverse(string1_preprocessed);
    clear_string_beginning(string1_preprocessed);

    char string2_preprocessed[string_length];
    strcpy(string2_preprocessed, string2);
    string_reverse(string2_preprocessed);
    clear_string_beginning(string2_preprocessed);

    return strcmp(string1_preprocessed, string2_preprocessed);
}

void sort_by_line_beginnings(size_t amount_of_lines, size_t max_line_len, char* text_to_parse)
{
    qsort(text_to_parse, amount_of_lines, max_line_len, strcmp_alphabetically_by_beginnings);
}

void sort_by_line_ends(size_t amount_of_lines, size_t max_line_len, char* text_to_parse)
{
    qsort(text_to_parse, amount_of_lines, max_line_len, strcmp_alphabetically_by_ends);
}
