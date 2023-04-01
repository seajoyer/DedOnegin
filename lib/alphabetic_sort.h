#ifndef SORT_BY_LINE_BEGINNINGS_H_
#define SORT_BY_LINE_BEGINNINGS_H_

#include <cstddef>

void sort_by_line_beginnings(size_t amount_of_lines, size_t max_line_len, char* text_to_parse);

void sort_by_line_ends(size_t amount_of_lines, size_t max_line_len, char* text_to_parse);

char* strrev(char* source_string, char* result_string);

#endif //SORT_BY_LINE_BEGINNINGS_H_
