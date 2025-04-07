/*
** EPITECH PROJECT, 2024
** my_strdup
** File description:
** my_strdup
*/

#include "my.h"
#include <stddef.h>
#include <stdlib.h>

char *my_strdup(char const *src)
{
    int i = 0;
    int lenght = my_strlen(src);
    char *str = malloc(sizeof(char) * lenght + 1);

    if (!str)
        return NULL;
    while (src[i] != '\0') {
        str[i] = src[i];
        i++;
    }
    str[i] = '\0';
    return str;
}
