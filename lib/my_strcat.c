/*
** EPITECH PROJECT, 2024
** my_strcat
** File description:
** my_strcat
*/

#include "shell.h"

// name :   my_strcat
// args :   destination string, string to copy
// use :    copy the src string at the end of dest
char *my_strcat(char *dest, char const *src)
{
    int j = my_strlen(dest);

    for (int k = 0; src[k] != '\0'; k++)
        dest[j + k] = src[k];
    dest[j + my_strlen(src)] = '\0';
    return dest;
}
