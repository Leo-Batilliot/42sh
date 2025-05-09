/*
** EPITECH PROJECT, 2025
** string_de_merde.c
** File description:
** utils_str
*/

#include "shell.h"
#include <stdlib.h>

static const char *delim = ";";
static const char *array[] = {"<", ">", "|", "&", NULL};
static const char *to_keep[] = {"(", ")", NULL};

int is_separator(char c, char *operator, const char *str, int pos)
{
    int i = 0;

    if (is_in_quotes(str, pos))
        return 0;
    while (operator && operator[i] != '\0') {
        if (c == operator[i])
            return 1;
        i++;
    }
    return 0;
}

int is_delim(const char c)
{
    for (int i = 0; delim[i] != '\0'; i++)
        if (c == delim[i])
            return 1;
    return 0;
}

int is_keep_alone(char c)
{
    for (int i = 0; to_keep[i]; i++)
        if (to_keep[i][0] == c)
            return 1;
    return 0;
}

int is_keep_delim(char c)
{
    for (int i = 0; array[i]; i++) {
        if (array[i][0] == c)
            return 1;
    }
    return 0;
}
