/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-minishell1-leo.batilliot
** File description:
** my_strncmp
*/
#include "my.h"

int my_strncmp(const char *str1, const char *str2, int n)
{
    if (!str1 || !str2 || my_strlen(str1) < n || my_strlen(str2) < n)
        return 84;
    for (int i = 0; i < n; i++)
        if (str1[i] != str2[i])
            return str1[i] - str2[i];
    return 0;
}
