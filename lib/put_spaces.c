/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** put_spaces.c
*/

#include <stdlib.h>

char *put_spaces(int index, int last_index)
{
    char *spaces = NULL;
    int i = 0;

    while (index > 9) {
        index /= 10;
        i++;
    }
    spaces = malloc(sizeof(char) * (i + last_index + 1));
    if (!spaces)
        return NULL;
    for (int j = 0; j < last_index - i; j++)
        spaces[j] = ' ';
    spaces[last_index - i] = '\0';
    return spaces;
}
