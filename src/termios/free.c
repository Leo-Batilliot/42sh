/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** free
*/
#include "line_edition.h"

int free_termios(termios_t *termios)
{
    if (!termios)
        return 0;
    if (termios->line)
        free(termios->line);
    if (termios->history_line)
        free(termios->history_line);
    free(termios);
    return 0;
}
