/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** termios_main
*/

#include "line_edition.h"
#include "unistd.h"

// name :   print_prompt
// args :   env list, prompt color
// use :    S.E
static int print_prompt(list_t *env, char *color)
{
    char *path = get_env_value("PWD", env);

    mini_printf(1, "%s%s> %s", color, path, colors[8].code);
    return 0;
}

// name :   display_line
// args :   termios main struct
// use :    S.E
static void display_line(termios_t *termios)
{
    mini_printf(1, "\r");
    mini_printf(1, "\033[K");
    print_prompt(termios->env, termios->prompt_color);
    mini_printf(1, "%s", termios->line);
    if (termios->pos < my_strlen(termios->line))
        mini_printf(1, "\033[%dD", my_strlen(termios->line) - termios->pos);
}

// name :   termios_loop
// args :   termios main struct
// use :    loops through and handle inputs until enter is pressed or read fail
static int termios_loop(termios_t *termios)
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
        display_line(termios);
    }
    return 0;
}

// name :   termios_main
// args :   main shell structure
// use :    init the termios structure, set the terminal settings and calls
//          the termios_loop
int termios_main(shell_t *shell)
{
    termios_t *termios = init_termios(shell);

    if (!termios)
        return 1;
    print_prompt(termios->env, termios->prompt_color);
    set_terminal_settings(1);
    termios_loop(termios);
    set_terminal_settings(0);
    shell->line = my_strdup(termios->line);
    free_termios(termios);
    return 0;
}
