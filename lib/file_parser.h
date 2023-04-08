#ifndef TEXT_PARSER_H_
#define TEXT_PARSER_H_

#include <stdio.h>

int min_line_in_file(FILE* file_pointer);

int max_line_in_file(FILE* file_pointer);

int min_line_length_in_file(FILE* file_pointer);

int max_line_length_in_file(FILE* file_pointer);

int amount_of_lines_in_file(FILE* file_pointer);

void file_to_array_of_strings(FILE* file_pointer, char* array_of_lines, size_t max_line_len);

#endif // TEXT_PARSER_H_
