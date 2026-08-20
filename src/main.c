#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/shell.h"
#include "../include/input.h"

int main()
{
    char *line;

    printf("=================================\n");
    printf("%s Version %s\n", SHELL_NAME, VERSION);
    printf("=================================\n");

    while(1)
    {
        printf("myshell> ");

        line = read_line();

        if(strcmp(line, "exit") == 0)
        {
            free(line);
            break;
        }

        if(strlen(line) != 0)
            printf("You entered : %s\n", line);

        free(line);
    }

    printf("Goodbye!\n");

    return 0;
}
