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
int print_prompt(list_t *env, char *color)
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

// name :   handle_eof
// args :   termios main struct, main shell struct
// use :    handle if crtl+d is not possible
static int handle_eof(termios_t *termios, shell_t *shell)
{
    if (termios->line[0] != '\0')
        return 0;
    if (termios->ignoreeof == 0)
        return 1;
    shell->ignoreeof--;
    if (shell->ignoreeof != 0)
        mini_printf(1, "\nUse 'exit' to quit.\n");
    return 1;
}

// name :   termios_loop
// args :   termios main struct
// use :    loops through and handle inputs until enter is pressed or read fail
static int termios_loop(termios_t *termios, shell_t *shell)
{
    int res = 0;
    int history = 0;

    while (read(0, &(termios->input), 1) > 0) {
        if (termios->input == 4 && handle_eof(termios, shell))
            return 1;
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

// name :   handle_exit_condition
// args :   termios main struct, main shell structure, int ret
// use :    check exit if ctrl+d is possible
static int handle_exit_condition(termios_t *termios, shell_t *shell, int ret)
{
    if (ret == 1) {
        if (shell->ignoreeof == 0) {
            mini_printf(1, "exit\n");
            termios->line = my_strcpy(termios->line, "exit");
            shell->line = NULL;
            free_termios(termios);
            return 1;
        }
        shell->line = my_strdup(termios->line);
        if (!shell->line)
            return -1;
    } else {
        shell->line = my_strdup(termios->line);
        if (!shell->line)
            return -1;
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
    int ret = 0;

    if (!termios)
        return 1;
    print_prompt(termios->env, termios->prompt_color);
    set_terminal_settings(1);
    ret = termios_loop(termios, shell);
    set_terminal_settings(0);
    if (handle_exit_condition(termios, shell, ret))
        return 1;
    free_termios(termios);
    return 0;
}
