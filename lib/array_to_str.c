/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-minishell1-leo.batilliot
** File description:
** array_to_str
*/
#include "my.h"

char *fill_str(const char **array, char *res, char delim)
{
    int count = 0;

    for (int i = 0; array[i]; i++) {
        for (int y = 0; array[i][y] != '\0'; y++) {
            res[count] = array[i][y];
            count++;
        }
        if (array[i + 1]) {
            res[count] = delim;
            count++;
        }
    }
    return res;
}

char *array_to_str(const char **array, char delim)
{
    int len = my_array_len((const void **) array);
    int slen = (len - 1);
    char *res = NULL;

    slen += total_array_len(array);
    res = malloc(sizeof(char) * (slen + 1));
    if (!res || !array || len == 0)
        return NULL;
    res = fill_str(array, res, delim);
    res[slen] = '\0';
    return res;
}
