/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-minishell1-gabin.wilson
** File description:
** my_exit
*/

#include "my.h"

void my_exit(char **array)
{
    int status_exit = 0;

    if (array[1])
        status_exit = atoi(array[1]);
    exit(status_exit);
}
