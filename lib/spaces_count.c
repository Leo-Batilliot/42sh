/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** spaces_count.c
*/

#include "shell.h"

// name :   count_digits
// args :   number
// use :    return the number of digits in the given number
int count_digits(int n)
{
    int count = 1;

    for (; n >= 10; count++)
        n /= 10;
    return count;
}

// name :   spaces_count
// args :   int current, int max
// use :    return the difference between the nb of digits of the two numbers
int spaces_count(int current, int max)
{
    return count_digits(max) - count_digits(current);
}
