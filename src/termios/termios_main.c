/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** termios_main
*/
#include "line_edition.h"
#include <termios.h>

int print_prompt(list_t *env)
{
    char *path = get_env_value("PWD", env);

    mini_printf(1, "%s> ", path);
    return 0;
}

void display_buffer(termios_t *termios)
{
    mini_printf(1, "\r");
    mini_printf(1, "\033[K");
    print_prompt(termios->env);
    mini_printf(1, "%s", termios->line);
    if (termios->pos < my_strlen(termios->line))
        mini_printf(1, "\033[%dD", my_strlen(termios->line) - termios->pos);
}

int termios_loop(termios_t *termios)
{
    int res = 0;
    int history = 0;

    while (read(0, &(termios->input), 1) > 0) {
        res = handle_input(termios);
        if (res != 2 && history)
            reset_termios_history(termios, &history);
        if (res == 2)
            history = 1;
        if (res == 1)
            return 0;
        display_buffer(termios);
    }
    return 0;
}

int termios_main(shell_t *shell)
{
    termios_t *termios = init_termios(shell);

    if (!termios)
        return 1;
    print_prompt(termios->env);
    set_terminal_settings(1);
    termios_loop(termios);
    set_terminal_settings(0);
    shell->line = my_strdup(termios->line);
    free_termios(termios);
    return 0;
}
