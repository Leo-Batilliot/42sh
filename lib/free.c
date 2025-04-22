/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-minishell1-leo.batilliot
** File description:
** free_array
*/
#include "my.h"

int my_free(void *ptr)
{
    if (!ptr)
        return 0;
    free(ptr);
    return 0;
}

int free_array(void **array)
{
    if (!array)
        return 0;
    for (int i = 0; array[i]; i++)
        free(array[i]);
    free(array);
    return 0;
}
