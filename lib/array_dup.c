/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** array_dup
*/

#include "shell.h"
#include <stdlib.h>
#include <stddef.h>

char **array_dup(char **array)
{
    char **new_array = NULL;
    int i = 0;

    if (!array)
        return NULL;
    new_array = malloc(sizeof(char *) * (array_len((const void **)array) + 1));
    if (!new_array)
        return NULL;
    for (; array[i]; i++) {
        new_array[i] = my_strdup(array[i]);
        if (!new_array[i]) {
            free_array((void **)new_array);
            return NULL;
        }
    }
    new_array[i] = NULL;
    return new_array;
}
