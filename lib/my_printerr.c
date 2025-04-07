/*
** EPITECH PROJECT, 2024
** print my_printerr
** File description:
** print my_printerr
*/

#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>
#include "my.h"

int my_put_debug(const char *string)
{
    for (int i = 0; string[i] != '\0'; i++)
        write(2, &string[i], 1);
    return 0;
}

int condition_err(const char *format, int i, va_list args, int *check)
{
    if (format[i] == 37 && format[i + 1] == 115) {
        my_put_debug(va_arg(args, char *));
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

int condition_errs(const char *format, int i, va_list args, int *check)
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

int my_printerr(const char *format, ...)
{
    int check = 1;
    va_list args;

    va_start(args, format);
    for (int i = 0; format[i] != '\0'; i++) {
        check = 1;
        i = condition_err(format, i, args, &check);
        i = condition_errs(format, i, args, &check);
        if (check == 1)
            write(2, &format[i], 1);
    }
    va_end(args);
    return 0;
}
