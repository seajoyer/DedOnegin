#include "alphabetic_sort.h"
#include "file_parser.h"
#include <assert.h>
#include <ctype.h>
#include <locale.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

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

void print_array_of_strings(char* arr, int amount_of_lines, int max_line_len)
{
    for (int i = 0; i < amount_of_lines; i++)
        printf("%s", arr + i * max_line_len);
}

FILE* open_file(const char file_name[], const char mode[])
{
    FILE* file_pointer = fopen(file_name, mode);
    assert(!(file_pointer == NULL) && "Could't read the file!\n");
    return file_pointer;
}

int main()
{
    setlocale(LC_ALL, "");

    // Read from file
    FILE* source_file = open_file("Eugene-Onegin.txt", "r");

    const size_t amount_of_lines = amount_of_lines_in_file(source_file);
    const size_t max_line_len = max_line_length_in_file(source_file) + 2; // Why +2?
    char array_of_strings[amount_of_lines][max_line_len];

    file_to_array_of_strings(source_file, &(array_of_strings[0][0]), max_line_len);

    // Write to file
    FILE* result_file = open_file("result.txt", "w");

    sort_by_line_beginnings(amount_of_lines, max_line_len, &(array_of_strings[0][0]));
    append_array_of_strings_to_file(result_file, &(array_of_strings[0][0]), amount_of_lines, max_line_len);

    sort_by_line_ends(amount_of_lines, max_line_len, &(array_of_strings[0][0]));
    append_array_of_strings_to_file(result_file, &(array_of_strings[0][0]), amount_of_lines, max_line_len);

    copy_file_to_another(source_file, result_file);

    fcloseall();
}
