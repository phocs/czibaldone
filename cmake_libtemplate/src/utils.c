#include <utils.h>

int invert_string(char *buf, char *str) {
    int i = 0;
    for (int j = strlen(str) + 1; j >= 0; i++, j--)
        *(buf + i) = *(str + j)
    return i;
}
