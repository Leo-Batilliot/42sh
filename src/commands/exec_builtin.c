/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** exec_builtin.c
*/

#include "my.h"

const builtin_t builtins[] = {
    {"env", exec_env},
    {"setenv", exec_setenv},
    {"unsetenv", exec_unsetenv},
    {"cd", my_cd},
    {"history", my_history},
    {"exit", my_exit},
    {"alias", alias},
    {NULL, NULL}
};

int exec_env(char **array, linked_list_t *head, shell_t *shell)
{
    return my_env(array, shell, &head);
}

int exec_setenv(char **array, linked_list_t *head, shell_t *shell)
{
    return my_setenv(&head, array, shell);
}

int exec_unsetenv(char **array, linked_list_t *head, shell_t *shell)
{
    return my_unsetenv(array, &head, shell);
}

int exec_builtin(char **array, linked_list_t *head, shell_t *shell)
{
    for (int i = 0; builtins[i].name != NULL; i++) {
        if (strcmp(array[0], builtins[i].name) == 0) {
            return builtins[i].func(array, head, shell);
        }
    }
    return 0;
}
