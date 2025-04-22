/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-minishell1-gabin.wilson
** File description:
** main
*/
#include "my.h"

static void reset_prompt(linked_list_t *head)
{
    char *path = get_env_value("PWD", head);

    if (isatty(0) == 1) {
        if (path)
            mini_printf(1, "%s> ", path);
        else
            mini_printf(1, "$> ");
    }
}

int main_loop(shell_t *shell, linked_list_t *head)
{
    while (1) {
        reset_prompt(head);
        if (!head)
            continue;
        if (getline(&shell->line, &shell->size, stdin) == -1)
            return shell->last_exit;
        if (!shell->line || shell->line[0] == '\n' || parse_args(shell) == 1)
            continue;
        if (add_to_history(shell, shell->line) == 1)
            continue;
        execute_command_list(shell, head);
    }
    return 0;
}

static int create_directory(char *directory)
{
    struct stat st = {0};

    if (stat(directory, &st) == -1) {
        if (mkdir(directory, 0755) != 0) {
            mini_printf(1, "Could not create the directory : %s\n", directory);
            return 84;
        }
    }
    return 0;
}

int load_file(shell_t *shell)
{
    create_directory("assets");
    if (isatty(0) == 1) {
        load_alias(shell);
        load_history(shell);
    }
    return 0;
}

int save_file(shell_t *shell)
{
    if (isatty(0) == 1) {
        write_alias(shell);
        write_history(shell);
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
    load_file(shell);
    res = main_loop(shell, head);
    save_file(shell);
    free_shell(shell);
    free_list(head);
    return res;
}
