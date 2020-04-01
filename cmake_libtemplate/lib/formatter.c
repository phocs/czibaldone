#include <formatter.h>

#include <string.h>
#include <stdarg.h>
#include <ctype.h>

int string_lower(char *buf) {
    int i = 0;
    for (; buf[i] != '\0'; i++)
        buf[i] = (char) tolower(buf[i]);
    return i;
}
