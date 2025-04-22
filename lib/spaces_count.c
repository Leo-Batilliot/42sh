/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** spaces_count.c
*/
#include "my.h"
#include <stdlib.h>

int count_digits(int n)
{
    int count = 1;

    for (; n >= 10; count++)
        n /= 10;
    return count;
}

int spaces_count(int current, int max)
{
    return count_digits(max) - count_digits(current);
}
