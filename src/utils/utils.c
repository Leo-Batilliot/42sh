/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** builtin_utils
*/

#include "shell.h"
#include <stddef.h>
#include <stdlib.h>

// name :   print_error
// args :   shell main struct, option
// use :    S.E
int print_error(shell_t *shell, int opt)
{
    if (!opt)
        mini_printf(2, "Invalid null command.\n");
    if (opt == 1)
        mini_printf(2, "Missing name for redirect.\n");
    shell->last_exit = 1;
    return 1;
}

// name :   my_env_cpy
// args :   env array
// use :    duplicate the env array
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

// name :   get_env_value
// args :   name string, env list
// use :    finds the value of an env variable using its name
char *get_env_value(const char *to_find, list_t *head)
{
    for (list_t *tmp = head; tmp; tmp = tmp->next)
        if (!my_strcmp(to_find, tmp->key))
            return tmp->value;
    return NULL;
}

// name :   is_operator
// args :   string
// use :    S.E
int is_operator(const char *str)
{
    const char *operators[] = {";", "|", "||", "&&"};

    for (unsigned long int j = 0;
        j < sizeof(operators) / sizeof(operators[0]); j++)
        if (!my_strcmp(str, operators[j]))
            return 1;
    return 0;
}
