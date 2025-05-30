/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-minishell1-leo.batilliot
** File description:
** total_array_len
*/

#include "shell.h"

// name :   total_array_len
// args :   an array
// use :    return the total length of every cell of the given array
int total_array_len(const char **array)
{
    int res = 0;

    if (!array)
        return res;
    for (int i = 0; array[i]; i++)
        res += my_strlen(array[i]);
    return res;
}
