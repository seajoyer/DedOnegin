#include "sort_text_by_beginnings.h"
#include <assert.h>
#include <cstddef>
#include <stdio.h>

int main()
{
    // FILE* file_pointer = fopen("Eugene-Onegin.txt", "r");
    FILE* file_pointer = fopen("test.txt", "r");
    assert(!(file_pointer == NULL) && "Could't read the file!");

    printf("%d", 1);

    char *buffer_pointer = NULL;
    size_t buffer_size = 0;
    ssize_t line_length;

    // while ((line_length = getline(&buffer_pointer, &buffer_size, file_pointer)) != -1) {

    // }
}
