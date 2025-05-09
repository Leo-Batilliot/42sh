/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** extract_condtiion.c
*/

#include "shell.h"
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

// name :   extract_condition
// args :   line (char *)
// use :    extracts the condition between "if" and "then" in a script line
char *extract_condition(char *line)
{
    char *start = NULL;
    char *end = NULL;
    char *condition = NULL;
    size_t len = 0;

    if (!line)
        return NULL;
    start = line + 2;
    while (*start && isspace(*start))
        start++;
    end = strstr(start, " then");
    if (!end)
        return NULL;
    len = end - start;
    condition = malloc(len + 1);
    if (!condition)
        return NULL;
    strncpy(condition, start, len);
    condition[len] = '\0';
    return condition;
}
