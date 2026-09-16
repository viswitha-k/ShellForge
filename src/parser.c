#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TOKEN_SIZE 64
#define TOKEN_DELIMITERS " \t\r\n\a"

char **parse_line(char *line)
{
    int size = TOKEN_SIZE;
    int position = 0;

    char **tokens = malloc(size * sizeof(char *));

    if (tokens == NULL)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    char *token = strtok(line, TOKEN_DELIMITERS);

    while (token != NULL)
    {
        tokens[position++] = token;

        if (position >= size)
        {
            size *= 2;

            tokens = realloc(tokens, size * sizeof(char *));

            if (tokens == NULL)
            {
                perror("realloc");
                exit(EXIT_FAILURE);
            }
        }

        token = strtok(NULL, TOKEN_DELIMITERS);
    }

    tokens[position] = NULL;

    return tokens;
}

void free_tokens(char **tokens)
{
    free(tokens);
}
