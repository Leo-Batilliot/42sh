/*
** EPITECH PROJECT, 2024
** mini printf
** File description:
** mini printf
*/

#include <stdarg.h>
#include <stdio.h>
#include "my.h"

int condition(const char *format, int i, va_list args, int *check)
{
    if (format[i] == 37 && format[i + 1] == 115) {
        my_putstr(va_arg(args, char *));
        i = i + 1;
        *check = 0;
    }
    if (format[i] == 37 && format[i + 1] == 37) {
        my_putchar('%');
        i = i + 1;
        *check = 0;
    }
    return i;
}

int condition_int(const char *format, int i, va_list args, int *check)
{
    if (format[i] == 37 && format[i + 1] == 105) {
        my_put_nbr(va_arg(args, int));
        i = i + 1;
        *check = 0;
    }
    if (format[i] == 37 && format[i + 1] == 100) {
        my_put_nbr(va_arg(args, int));
        i = i + 1;
        *check = 0;
    }
    if (format[i] == 37 && format[i + 1] == 99) {
        my_putchar(va_arg(args, int));
        i = i + 1;
        *check = 0;
    }
    return i;
}

int mini_printf(const char *format, ...)
{
    int check = 1;
    va_list args;

    va_start(args, format);
    for (int i = 0; format[i] != '\0'; i++) {
        check = 1;
        i = condition(format, i, args, &check);
        i = condition_int(format, i, args, &check);
        if (check == 1)
            my_putchar(format[i]);
    }
    va_end(args);
    return 0;
}
