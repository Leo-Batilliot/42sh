/*
** EPITECH PROJECT, 2025
** G-AIA-200-LIL-2-1-cuddle-leo.batilliot
** File description:
** str_lowcase
*/
#include "my.h"

char *str_lowcase(char *str)
{
    if (!str)
        return NULL;
    for (int i = 0; str[i] != '\0'; i++)
        if (str[i] >= 'A' && str[i] <= 'Z')
            str[i] -= 'A' - 'a';
    return str;
}
