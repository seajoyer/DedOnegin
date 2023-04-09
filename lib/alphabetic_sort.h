#ifndef SORT_BY_LINE_BEGINNINGS_H_
#define SORT_BY_LINE_BEGINNINGS_H_

#include <cstddef>

void clear_string_beginning(char* string);

int strcmp_alphabetically_by_beginnings(void const* void_string1, void const* void_string2);

int strcmp_alphabetically_by_ends(void const* void_string1, void const* void_string2);

void sort_by_line_beginnings(size_t amount_of_lines, size_t max_line_len, char* text_to_parse);

void sort_by_line_ends(size_t amount_of_lines, size_t max_line_len, char* text_to_parse);

#endif // SORT_BY_LINE_BEGINNINGS_H_
