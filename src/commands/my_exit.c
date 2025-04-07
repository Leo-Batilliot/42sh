/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-minishell1-gabin.wilson
** File description:
** my_exit
*/

#include "my.h"
#include <stdlib.h>

void free_all(char **env_cpy, char **array)
{
    for (int i = 0; env_cpy[i] != NULL; i++)
        free(env_cpy[i]);
    free(env_cpy);
    for (int i = 0; array[i] != NULL; i++)
        free(array[i]);
    free(array);
}

void my_exit(char **array)
{
    int statu_exit = 0;

    if (my_strcmp(array[0], "exit") == 0) {
        if (array[1] != NULL)
            statu_exit = my_getnbr(array[1]);
        exit(statu_exit);
    }
}
