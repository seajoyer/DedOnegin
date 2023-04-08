#include "alphabetic_sort.h"
#include "file_parser.h"
#include <assert.h>
#include <cstddef>
#include <stdio.h>
#include <string.h>

void print_array_of_strings(char* arr, int amount_of_lines, int max_line_len)
{
    for (int i = 0; i < amount_of_lines; i++) {
        printf("%s", arr + i * max_line_len);
    }
}

FILE* open_file(const char file_name[], const char mode[])
{
    FILE* file_pointer = fopen(file_name, mode);
    // FILE* file_pointer = fopen("test.txt", "r");
    assert(!(file_pointer == NULL) && "Could't read the file!\n");
    return file_pointer;
}

int main()
{
    FILE* file_pointer = open_file("test.txt", "r");
    // FILE* file_pointer = open_file("Eugene-Onegin.txt", "r");

    const size_t amount_of_lines = amount_of_lines_in_file(file_pointer);
    const size_t max_line_len = max_line_length_in_file(file_pointer) + 2; // Why +2?

    char array_of_lines[amount_of_lines][max_line_len];

    file_to_array_of_strings(file_pointer, &(array_of_lines[0][0]), max_line_len);

    print_array_of_strings(&(array_of_lines[0][0]), amount_of_lines, max_line_len);

    // sort_by_line_ends(amount_of_lines, max_line_len, &(array_of_lines[0][0]));
    // printf("@@@\n");
    // print_array_of_strings(&(array_of_lines[0][0]), amount_of_lines, max_line_len);

    fcloseall();
}
