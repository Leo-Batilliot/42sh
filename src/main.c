/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-minishell1-gabin.wilson
** File description:
** main
*/
#include "my.h"

static void reset_prompt(void)
{
    if (isatty(0) == 1)
        printf("$> ");
}

int main_loop(shell_t *shell, linked_list_t *head)
{
    while (1) {
        reset_prompt();
        if (!head)
            continue;
        if (getline(&shell->line, &shell->size, stdin) == -1)
            return shell->last_exit;
        if (add_to_history(shell, shell->line) == 1)
            continue;
        if (!shell->line || shell->line[0] == '\n' || parse_args(shell) == 1)
            continue;
        execute_command_list(shell, head);
    }
    return 0;
}

int main(int ac, char **av, char **env)
{
    shell_t *shell = NULL;
    linked_list_t *head = NULL;
    int res = 84;

    (void)av;
    if (ac != 1)
        return res;
    shell = init_shell(env);
    if (!shell)
        return res;
    head = init_env(shell->env_cpy);
    if (!head)
        return res;
    load_history(shell);
    res = main_loop(shell, head);
    free_shell(shell);
    free_list(head);
    return res;
}
