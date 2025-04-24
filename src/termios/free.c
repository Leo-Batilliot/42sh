/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** free
*/

#include "line_edition.h"

// name :   free_termios
// args :   termios main struct
// use :    S.E
int free_termios(termios_t *termios)
{
    if (!termios)
        return 0;
    if (termios->line)
        my_free(termios->line);
    if (termios->history_line)
        my_free(termios->history_line);
    my_free(termios);
    return 0;
}
