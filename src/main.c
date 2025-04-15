/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-minishell1-gabin.wilson
** File description:
** main
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include "my.h"

int get_cur_pass(linked_list_t **head, char **array, info_shell_t *shell_i)
{
    char *string_path = NULL;
    char *string_pwd = NULL;

    string_path = get_env_value("PATH", *head);
    string_pwd = get_env_value("PWD", *head);
    shell_i->path = get_path(array[0], string_path, string_pwd);
    if (!shell_i->path) {
        fprintf(stderr, "%s: Command not found.\n", array[0]);
        shell_i->last_exit = 1;
        return 1;
    }
    return 0;
}

int gest_loop(info_shell_t *shell_i, args_t *tmp, linked_list_t **head)
{
    shell_i->env_cpy = linked_list_to_array((*head));
    if (!shell_i->env_cpy)
        return 0;
    my_gest_exec(shell_i, tmp, head);
    free_all(shell_i->env_cpy, tmp->args);
    return 0;
}

info_shell_t *declare_struct(char **env)
{
    info_shell_t *shell_i = malloc(sizeof(info_shell_t));

    if (!shell_i)
        return NULL;
    shell_i->path = NULL;
    shell_i->line = NULL;
    shell_i->save_old = NULL;
    shell_i->last_exit = 0;
    shell_i->size = 0;
    shell_i->res = 0;
    shell_i->prev = 0;
    shell_i->env_cpy = my_env_cpy(env);
    if (!shell_i->env_cpy)
        return NULL;
    return shell_i;
}

static void reset_prompt(void)
{
    if (isatty(0) == 1)
        printf("$> ");
}

static int execute_command_list(info_shell_t *shell_i, linked_list_t *head)
{
    args_t *tmp = shell_i->list->head;

    for (; tmp; tmp = tmp->next) {
        if (gest_cur_commands(tmp->args, head, shell_i) == -1)
            continue;
        gest_loop(shell_i, tmp, &head);
    }
    shell_i->list = NULL;
    return 0;
}

int main_loop(info_shell_t *shell_i, linked_list_t *head)
{
    while (1) {
        reset_prompt();
        if (!head)
            continue;
        if (getline(&shell_i->line, &shell_i->size, stdin) == -1)
            return shell_i->last_exit;
        if (shell_i->line[0] == '\n' || parse_args(shell_i) == ERROR)
            continue;
        if (execute_command_list(shell_i, head) == ERROR)
            continue;
    }
    return 0;
}

int main(int ac, char **av, char **env)
{
    info_shell_t *shell_i = NULL;
    linked_list_t *head = NULL;

    (void)av;
    shell_i = declare_struct(env);
    if (ac != 1 || !shell_i)
        return 84;
    head = init_env_list(shell_i->env_cpy);
    return main_loop(shell_i, head);
}
