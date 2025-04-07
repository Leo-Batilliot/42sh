/*
** EPITECH PROJECT, 2024
** my_putstr
** File description:
** display one caracter per one
*/

#include "my.h"

int my_putstr(char const *str)
{
    while (*str != '\0') {
        my_putchar(*str);
        str = str + 1;
    }
    return 0;
}
