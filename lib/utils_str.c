/*
** EPITECH PROJECT, 2025
** string_de_merde.c
** File description:
** utils_str
*/

#include <shell.h>
#include <stdlib.h>

static const char *delim = ";";
static const char *array[] = {"<", ">", "|", "&", NULL};
static const char *to_keep[] = {"(", ")", "\"", NULL};

int is_separator(const char c, char *ope)
{
    for (int i = 0; ope[i] != '\0'; i++)
        if (c == ope[i])
            return 1;
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
