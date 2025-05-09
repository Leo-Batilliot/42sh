/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-minishell1-gabin.wilson
** File description:
** main
*/

#include "shell.h"
#include <stddef.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdlib.h>

// name :   line
// args :   shell main struct
// use :    use getline or termios to get the line info depending on isatty(0)
static int line(shell_t *shell)
{
    size_t size;

    if (isatty(0))
        return termios_main(shell);
    else
        if (getline(&shell->line, &size, stdin) == -1)
            return 1;
    return 0;
}

// name :   main_loop_command
// args :   shell main struct
// use :    execute the command after the parsing
int main_loop_command(shell_t *shell)
{
    free_array((void **)shell->env_cpy);
    shell->env_cpy = list_to_array(shell->env);
    if (!shell->env_cpy)
        return 1;
    execute_node(shell->root, shell->env_cpy, shell);
    return 0;
}

// name :   main_loop_parsing
// args :   shell main struct
// use :    get line input from user and parse it
int main_loop_parsing(shell_t *shell)
{
    char **tokens = NULL;

    while (1) {
        if (!shell->env || line(shell))
            return shell->last_exit;
        if (!shell->line || shell->line[0] == '\n' ||
            add_to_history(shell, shell->line))
            continue;
        tokens = split_str(shell->line, " \t\n");
        if (!tokens)
            continue;
        free_nodes(shell->root);
        shell->root = parse_tokens(tokens, 0,
            array_len((const void **)tokens), shell);
        free_array((void **)tokens);
        if (main_loop_command(shell))
            return 0;
    }
    return 0;
}

// name :   main
// args :   arguments count, arguments value, env
// use :    init the shell, env, and assets before starting the main loop
int main(int ac, char **av, char **env)
{
    shell_t *shell = NULL;
    int res = 84;

    (void)av;
    if (ac != 1)
        return res;
    handle_signals();
    shell = init_shell(env);
    if (!shell)
        return res;
    shell->env = init_env(shell->env_cpy);
    if (!shell->env)
        free_and_exit(shell, res);
    load_file(shell);
    free_and_exit(shell, main_loop_parsing(shell));
    return 84;
}
