/*
** EPITECH PROJECT, 2025
** mini printf
** File description:
** mini print f
*/
#include "my.h"
#include <stdio.h>
#include <stdarg.h>

void my_putchar(int output, char c)
{
    write(output, &c, 1);
}

void my_put_nbr(int output, long nb)
{
    char res;

    if (nb < 0) {
        write(output, "-", 1);
        nb = - nb;
    }
    if (nb >= 10) {
        my_put_nbr(output, nb / 10);
    }
    res = nb % 10 + '0';
    my_putchar(output, res);
}

void putstr(int output, char *str)
{
    if (!str)
        return;
    write(output, str, my_strlen(str));
}

void process_format(int output, char specifier, va_list ap)
{
    switch (specifier) {
        case 's':
            putstr(output, va_arg(ap, char *));
            break;
        case 'd':
            my_put_nbr(output, va_arg(ap, int));
            break;
        case 'i':
            my_put_nbr(output, va_arg(ap, int));
            break;
        case 'c':
            my_putchar(output, (char) va_arg(ap, int));
            break;
        case '%':
            return my_putchar(output, '%');
        case 'l':
            my_put_nbr(output, va_arg(ap, long int));
            break;
    }
}

int mini_printf(int output, char *format, ...)
{
    va_list ap;

    va_start(ap, format);
    while (*format) {
        if (*format == '%') {
            format++;
            process_format(output, *format, ap);
            format++;
        } else {
            my_putchar(output, *format);
            format++;
        }
    }
    va_end(ap);
    return 0;
}
