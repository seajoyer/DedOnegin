#ifndef SORT_BY_LINE_BEGINNINGS_H_
#define SORT_BY_LINE_BEGINNINGS_H_

#include <cstddef>

int utf8_charsize(char* ch);

int utf8_is_continuation(char character);

size_t utf8_strlen(char* s);

void sort_by_line_beginnings(size_t amount_of_lines, size_t max_line_len, char* text_to_parse);

void sort_by_line_ends(size_t amount_of_lines, size_t max_line_len, char* text_to_parse);

char* string_reverse(char* string);

#endif //SORT_BY_LINE_BEGINNINGS_H_
