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
        fprintf(stderr, "Invalid null command.\n");
    if (opt == 1)
        fprintf(stderr, "Missing name for redirect.\n");
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

char *get_env_value(const char *to_find, linked_list_t *head)
{
    for (linked_list_t *tmp = head; tmp; tmp = tmp->next)
        if (!strcmp(to_find, tmp->key))
            return tmp->value;
    return NULL;
}

int is_operator(const char *str)
{
    const char *operators[] = {";", ">>", "<<", "<", "|", ">"};

    for (int j = 0; j < 6; j++)
        if (!my_strcmp(str, operators[j]))
            return 1;
    return 0;
}

int is_builtin(char *cmd)
{
    if (!my_strcmp(cmd, "env")
        || !my_strcmp(cmd, "setenv")
        || !my_strcmp(cmd, "unsetenv")
        || !my_strcmp(cmd, "exit")
        || !my_strcmp(cmd, "cd")) {
        return 1;
    }
    return 0;
}
