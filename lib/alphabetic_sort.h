#ifndef SORT_BY_LINE_BEGINNINGS_H_
#define SORT_BY_LINE_BEGINNINGS_H_

#include <cstddef>

void lowercase_string(char* string);

void clear_string_untill_alpha(char* string);

int compare_strings_alphabetically(void const* void_string1, void const* void_string2, int direction);

int compare_strings_alphabetically_by_beginnings(void const* void_string1, void const* void_string2);

int compare_strings_alphabetically_by_ends(void const* void_string1, void const* void_string2);

void sort_strings_by_beginnings(size_t amount_of_lines, size_t max_line_len, char* text_to_parse);

void sort_strings_by_ends(size_t amount_of_lines, size_t max_line_len, char* text_to_parse);

#endif // SORT_BY_LINE_BEGINNINGS_H_
