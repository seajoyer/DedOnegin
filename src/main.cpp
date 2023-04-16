#include "alphabetic_sort.h"
#include "file_parser.h"
#include "sorting_algorithms.h"
#include <assert.h>
#include <cstdlib>
#include <ctype.h>
#include <locale.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

FILE* open_file(const char file_name[], const char mode[])
{
    FILE* file_pointer = fopen(file_name, mode);
    if (!file_pointer)
        printf("Couldn't read the file!\n");
    return file_pointer;
}

void append_array_of_strings_to_file(FILE* result_file, char* array_of_strings, size_t amount_of_lines, size_t max_line_length)
{
    for (size_t i = 0; i < amount_of_lines; i++)
        fprintf(result_file, "%s", array_of_strings + i * max_line_length);
}

void copy_file_to_another(FILE* source_file, FILE* result_file)
{
    if (!source_file || !result_file) {
        printf("Could't read the file!");
    }

    rewind(source_file);

    char* buffer_pointer = NULL;
    size_t buffer_size = 0;

    while (getline(&buffer_pointer, &buffer_size, source_file) != -1)
        fprintf(result_file, "%s", buffer_pointer);
}

int main()
{
    setlocale(LC_ALL, "");

    FILE* source_file = open_file("Eugene-Onegin.txt", "r");

    const size_t amount_of_lines = amount_of_lines_in_file(source_file);
    const size_t max_line_len = max_line_length_in_file(source_file);
    char array_of_strings[amount_of_lines][max_line_len];
    file_to_array_of_strings(source_file, &(array_of_strings[0][0]), max_line_len);

    FILE* result_file = open_file("out.txt", "w");

    sort_strings_by_beginnings(amount_of_lines, max_line_len, &(array_of_strings[0][0]));
    append_array_of_strings_to_file(result_file, &(array_of_strings[0][0]), amount_of_lines, max_line_len);

    sort_strings_by_ends(amount_of_lines, max_line_len, &(array_of_strings[0][0]));
    append_array_of_strings_to_file(result_file, &(array_of_strings[0][0]), amount_of_lines, max_line_len);

    copy_file_to_another(source_file, result_file);

    fcloseall();
}
