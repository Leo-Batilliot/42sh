/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** init
*/

#include "line_edition.h"
#include <termios.h>
#include <stdlib.h>
#include <stddef.h>
#include <unistd.h>

// name :   set_terminal_settings
// args :   enable/disable
// use :    save and restore old settings and set new settings for termios
int set_terminal_settings(int enable)
{
    static struct termios old;
    struct termios new;

    if (!enable) {
        tcsetattr(STDIN_FILENO, TCSANOW, &old);
        return 0;
    }
    tcgetattr(STDIN_FILENO, &old);
    new = old;
    new.c_lflag &= ~(ICANON | ECHO);
    new.c_cc[VMIN] = 1;
    new.c_cc[VTIME] = 0;
    tcsetattr(STDIN_FILENO, TCSANOW, &new);
    return 0;
}

// name :   init_termios_variables
// args :   termios main struct, shell main struct
// use :    S.E
static void init_termios_variables(termios_t *termios, shell_t *shell)
{
    termios->history_pos = 0;
    termios->history_index = 0;
    termios->history_line = NULL;
    termios->line[0] = '\0';
    termios->env = shell->env;
    termios->history = shell->history;
    termios->prompt_color = shell->prompt_color;
    termios->input = '\0';
    termios->pos = 0;
}

// name :   init_termios
// args :   shell main struct
// use :    init a termios structure and set it variables
termios_t *init_termios(shell_t *shell)
{
    termios_t *termios;

    if (shell->line)
        my_free(shell->line);
    shell->line = NULL;
    termios = malloc(sizeof(termios_t));
    if (!termios)
        return NULL;
    termios->line = malloc(sizeof(char) * BUFFER_SIZE);
    if (!termios->line) {
        my_free(termios);
        return NULL;
    }
    init_termios_variables(termios, shell);
    return termios;
}
