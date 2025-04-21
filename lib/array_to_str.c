/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** array_to_str
*/

#include "my.h"

char *array_to_str(char **array)
{
    int total_len = 0;
    char *result = NULL;
    int i = 0;

    if (!array)
        return NULL;
    for (i = 0; array[i]; i++)
        total_len += strlen(array[i]) + 1;
    result = malloc(sizeof(char) * total_len);
    if (!result)
        return NULL;
    result[0] = '\0';
    for (i = 0; array[i]; i++) {
        strcat(result, array[i]);
        if (array[i + 1])
            strcat(result, " ");
    }
    return result;
}
