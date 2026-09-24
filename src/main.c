#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/shell.h"
#include "../include/input.h"
#include "../include/parser.h"
#include "../include/process.h"
#include "../include/builtin.h"
#include "../include/signals.h"

int main()
{
    char *line;
    char **tokens;

    initialize_signals();

    printf("=====================================\n");
    printf("ShellForge Version 6.0\n");
    printf("=====================================\n");

    while (1)
    {
        printf("myshell> ");

        line = read_line();

        if (strcmp(line, "exit") == 0)
        {
            free(line);
            break;
        }

        tokens = parse_line(line);

        if (tokens[0] != NULL)
        {
            if (execute_builtin(tokens) == 0)
            {
                execute(tokens);
            }
        }

        free_tokens(tokens);
        free(line);
    }

    printf("Goodbye!\n");

    return 0;
}
