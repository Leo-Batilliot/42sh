/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** put_spaces.c
*/

#include <stdlib.h>

char *put_spaces(int index)
{
    int i = 0;
    int temp = index;
    char *spaces = NULL;

    while (temp > 9) {
        temp /= 10;
        i++;
    }
    spaces = malloc(sizeof(char) * (i + 5));
    if (!spaces)
        return NULL;
    for (int j = 0; j < 4 - i; j++)
        spaces[j] = ' ';
    spaces[4 - i] = '\0';
    return spaces;
}
