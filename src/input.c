#include <stdio.h>
#include <stdlib.h>
#include "input.h"

#define INITIAL_SIZE 64

char *read_line(void)
{
    int size = INITIAL_SIZE;
    int position = 0;

    char *buffer = malloc(size);

    if(buffer == NULL)
    {
        fprintf(stderr, "Memory Allocation Failed\n");
        exit(EXIT_FAILURE);
    }

    int ch;

    while(1)
    {
        ch = getchar();

        if(ch == EOF || ch == '\n')
        {
            buffer[position] = '\0';
            return buffer;
        }

        buffer[position++] = ch;

        if(position >= size)
        {
            size *= 2;

            buffer = realloc(buffer, size);

            if(buffer == NULL)
            {
                fprintf(stderr, "Memory Allocation Failed\n");
                exit(EXIT_FAILURE);
            }
        }
    }
}
