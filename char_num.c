#include "incl.h"

int char_num(char * buff, int max)
{
    int i = 0;
    for (i = 0; buff[i] != EOF, buff[i] != '\n', buff[i] != '\0'; i++)
        if (i == max)
        {
            buff[i] = '\0';
            return (i-1);
        }
    return i;
}
