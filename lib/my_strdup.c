/*
** EPITECH PROJECT, 2024
** my_strdup
** File description:
** my_strdup
*/

#include "shell.h"
#include <stddef.h>
#include <stdlib.h>

// name :   my_strdup
// args :   source string
// use :    return a duplicate of the source string
char *my_strdup(char const *src)
{
    int i = 0;
    char *str;

    if (!src)
        return NULL;
    str = malloc(sizeof(char) * my_strlen(src) + 1);
    if (!str)
        return NULL;
    for (; src[i] != '\0'; i++)
        str[i] = src[i];
    str[i] = '\0';
    return str;
}
