/*
** EPITECH PROJECT, 2024
** my_strcpy
** File description:
** return string into another
*/

#include "stddef.h"

// name :   my_strcpy
// args :   destination string, source string
// use :    copy the source string in the destination string
char *my_strcpy(char *dest, char const *src)
{
    int i = 0;

    if (!src)
        return NULL;
    for (; src[i] != '\0'; i++)
        dest[i] = src[i];
    dest[i] = '\0';
    return dest;
}
