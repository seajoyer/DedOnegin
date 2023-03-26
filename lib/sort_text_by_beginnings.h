#ifndef SORT_BY_LINE_BEGINNINGS_H_
#define SORT_BY_LINE_BEGINNINGS_H_

#include <stdio.h>

int amount_of_lines(FILE *file_pointer);

int min_line(char text_to_parse[]);

void sort_by_line_beginnings(int max_line_length, char text_to_parse[][max_line_length]);

#endif //SORT_BY_LINE_BEGINNINGS_H_
