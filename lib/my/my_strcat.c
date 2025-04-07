/*
** EPITECH PROJECT, 2024
** my_strcat
** File description:
** my_strcat
*/

#include "my.h"

char *my_strcat(char *dest, char const *src)
{
    int j = my_strlen(dest);

    for (int k = 0; src[k] != '\0'; k++) {
        dest[j + k] = src[k];
    }
    dest[j + my_strlen(src)] = '\0';
    return dest;
}
