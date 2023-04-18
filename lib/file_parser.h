#ifndef TEXT_PARSER_H_
#define TEXT_PARSER_H_

#include <stdio.h>

size_t shortest_string_in_file(FILE* file_pointer);

size_t longest_string_in_file(FILE* file_pointer);

size_t min_string_length_in_file(FILE* file_pointer);

size_t get_max_line_len(FILE* file_pointer);

size_t get_line_count(FILE* file_pointer);

void file_to_array_of_strings(FILE* file_pointer, char* array_of_lines, size_t max_line_len);

#endif // TEXT_PARSER_H_
