#include "alphabetic_sort.h"
#include "sorting_algorithms.h"
#include "utf8_string_tools.h"
#include <assert.h>
#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wctype.h>

void lowercase_string(char* string)
{
    size_t line_length = 1;
    while (string[line_length] != '\0')
        line_length++;

    wchar_t wbuffer[line_length];
    mbstowcs(wbuffer, string, line_length);

    for (size_t i = 0; i < line_length; i++) {
        wbuffer[i] = towlower(wbuffer[i]);
    }
    wcstombs(string, wbuffer, line_length);
}

void clear_string_untill_alpha(char* string)
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

int compare_strings_alphabetically(void const* void_string1, void const* void_string2, int direction)
{
    char const* string1 = (char const*)void_string1;
    char const* string2 = (char const*)void_string2;

    size_t string_length = 1;
    for (int first_end_gained = 0, second_end_gained = 0; !(first_end_gained && second_end_gained); string_length++) {
        if (!first_end_gained && string1[string_length] == '\0')
            first_end_gained = 1;
        if (!second_end_gained && string2[string_length] == '\0')
            second_end_gained = 1;
    }

    char string1_preprocessed[string_length];
    strcpy(string1_preprocessed, string1);
    if (direction < 0)
        string_reverse(string1_preprocessed);
    clear_string_untill_alpha(string1_preprocessed);
    lowercase_string(string1_preprocessed);

    char string2_preprocessed[string_length];
    strcpy(string2_preprocessed, string2);
    if (direction < 0)
        string_reverse(string2_preprocessed);
    clear_string_untill_alpha(string2_preprocessed);
    lowercase_string(string2_preprocessed);

    return strcmp(string1_preprocessed, string2_preprocessed);
}

int compare_strings_alphabetically_by_beginnings(void const* void_string1, void const* void_string2)
{
    return compare_strings_alphabetically(void_string1, void_string2, 1);
}

int compare_strings_alphabetically_by_ends(void const* void_string1, void const* void_string2)
{
    return compare_strings_alphabetically(void_string1, void_string2, -1);
}

void sort_strings_by_beginnings(size_t amount_of_lines, size_t max_line_len, char* text_to_parse)
{
    quick_sort(text_to_parse, amount_of_lines, max_line_len, compare_strings_alphabetically_by_beginnings);
}

void sort_strings_by_ends(size_t amount_of_lines, size_t max_line_len, char* text_to_parse)
{
    quick_sort(text_to_parse, amount_of_lines, max_line_len, compare_strings_alphabetically_by_ends);
}
