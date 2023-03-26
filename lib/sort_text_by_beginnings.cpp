#include "sort_text_by_beginnings.h"
#include <string.h>

int amount_of_lines(FILE *file_pointer) {
    unsigned int amount = 0, character;
    while ((character = fgetc(file_pointer)) != EOF) {
        ++amount;
    }
    return amount;
}

int min_line(char text_to_parse[]) {
    int min_line_index = 0;
    for (int i = 1; i < sizeof(text_to_parse[0]); i++) {
        if (text_to_parse[i] < text_to_parse[min_line_index]) {
            min_line_index = i;
        }
    }
}

void sort_by_line_beginnings(int max_line_length, char text_to_parse[][max_line_length]) {
    char current_line[max_line_length];
    for (int i = 0; i < max_line_length; i++) {

    }
}
