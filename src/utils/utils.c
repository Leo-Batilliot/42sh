/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** builtin_utils
*/
#include "my.h"

int print_error(shell_t *shell, int opt)
{
    if (!opt)
        mini_printf(2, "Invalid null command.\n");
    if (opt == 1)
        mini_printf(2, "Missing name for redirect.\n");
    shell->last_exit = 1;
    return 1;
}

char **my_env_cpy(char **env)
{
    char **env_cpy = NULL;
    int i = 0;

    env_cpy = malloc(sizeof(char *) * (array_len((const void **)env) + 1));
    if (!env_cpy)
        return NULL;
    for (; env[i]; i++) {
        env_cpy[i] = malloc(sizeof(char) * my_strlen(env[i]) + 1);
        if (!env_cpy[i])
            return NULL;
        my_strcpy(env_cpy[i], env[i]);
    }
    env_cpy[i] = NULL;
    return env_cpy;
}

char *get_env_value(const char *to_find, list_t *head)
{
    for (list_t *tmp = head; tmp; tmp = tmp->next)
        if (!strcmp(to_find, tmp->key))
            return tmp->value;
    return NULL;
}

int is_operator(const char *str)
{
    const char *operators[] = {";", ">>", "<<", "<", "|", ">", "&&"};

    for (int j = 0; j < 7; j++)
        if (!my_strcmp(str, operators[j]))
            return 1;
    return 0;
}

int is_builtin(char **cmds)
{
    if (!my_strcmp(cmds[0], "env")
        || !my_strcmp(cmds[0], "setenv")
        || !my_strcmp(cmds[0], "unsetenv")
        || !my_strcmp(cmds[0], "exit")
        || !my_strcmp(cmds[0], "cd")
        || !my_strcmp(cmds[0], "alias")
        || !my_strcmp(cmds[0], "history")) {
        return 1;
    }
    if (!my_strcmp(cmds[0], "clean")) {
        if (!cmds[1])
            return 1;
        if (!my_strcmp(cmds[1], "history")) {
            return 1;
        }
    }
    return 0;
}
