/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** array_to_str
*/

#include "shell.h"
#include <stddef.h>
#include <stdlib.h>

// name :   array_to_str
// args :   a char **array
// use :    concatenates the array into one string (separating with a spaces)
char *array_to_str(char **array)
{
    int total_len = 0;
    char *result = NULL;
    int i = 0;

    if (!array)
        return NULL;
    for (i = 0; array[i]; i++)
        total_len += my_strlen(array[i]) + 1;
    result = malloc(sizeof(char) * total_len);
    if (!result)
        return NULL;
    result[0] = '\0';
    for (i = 0; array[i]; i++) {
        my_strcat(result, array[i]);
        if (array[i + 1])
            my_strcat(result, " ");
    }
    return result;
}
