/*
** EPITECH PROJECT, 2024
** my_strcpy
** File description:
** return string into another
*/

#include "stddef.h"
#include "shell.h"

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

// name :   strcpy_from
// args :   destination string, src string, start position
// use :    copy the src string into dest, starting from the position given
char *strcpy_from(char *dest, char *src, int start)
{
    if (!dest || !src)
        return dest;
    for (int i = 0; src[i] != '\0'; i++)
        dest[i + start] = src[i];
    dest[start + my_strlen(src)] = '\0';
    return dest;
}
