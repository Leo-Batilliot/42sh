/*
** EPITECH PROJECT, 2024
** my_strcmp
** File description:
** behavior of strcmp
*/

#include "shell.h"

// name :   my_strcmp
// args :   string 1, string 2
// use :    compares the strings and return the ascii difference if found
int my_strcmp(char const *s1, char const *s2)
{
    if (!s1 || !s2 || my_strlen(s1) != my_strlen(s2))
        return 84;
    for (int i = 0; s1[i] != '\0'; i++)
        if (s1[i] != s2[i])
            return s1[i] - s2[i];
    return 0;
}
