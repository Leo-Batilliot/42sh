/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-minishell2-leo.batilliot
** File description:
** strtrim
*/

#include "shell.h"
#include "stddef.h"

// name :   strtrim
// args :   a string
// use :    return a duplicate cleaned string (no ' ' or '\t' at the start/end)
char *strtrim(char *str)
{
    char *start = NULL;

    if (!str)
        return NULL;
    for (start = str; (*start == ' ' || *start == '\t'); start++);
    if (!*start) {
        *str = '\0';
        return str;
    }
    for (; start[my_strlen(start) - 1] == ' ' || start[my_strlen(start) - 1] ==
        '\t'; start[my_strlen(start) - 1] = '\0');
    start = my_strdup(start);
    my_free(str);
    return start;
}
