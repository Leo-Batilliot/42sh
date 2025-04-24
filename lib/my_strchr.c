/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-minishell1-gabin.wilson
** File description:
** my_strchr
*/

#include <stdlib.h>

// name :   my_strchr
// args :   a string, the character to find
// use :    when the character is found, return the rest of the string
char *my_strchr(char *string, int ope)
{
    for (int i = 0; string[i] != '\0'; i++) {
        if (string[i] == ope)
            return string + i;
    }
    return NULL;
}
