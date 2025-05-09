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

// name :   my_null_strdup
// args : a string
// use : return NULL if the string is empty, strdup otherwise
char *my_null_strdup(char *str)
{
    if (!str || str[0] == '\0')
        return NULL;
    return my_strdup(str);
}

// name :   my_strndup
// args :   a string, a number
// use :    return a duplicate string of the first N characters of src
char *my_strndup(char const *src, int n)
{
    char *str = NULL;

    if (!src || my_strlen(src) < n || n < 1)
        return NULL;
    str = malloc(sizeof(char) * n + 1);
    if (!str)
        return NULL;
    for (int i = 0; i < n; i++)
        str[i] = src[i];
    str[n] = '\0';
    return str;
}
