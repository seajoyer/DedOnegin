#include <stddef.h>

int utf8_is_continuation(char ch);

int utf8_charsize(char* ch);

size_t utf8_strlen(char* str);

char* string_reverse(char* string);
