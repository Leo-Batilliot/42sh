/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-minishell1-gabin.wilson
** File description:
** my_setenv
*/

#include "shell.h"
#include <stddef.h>
#include <stdlib.h>

// name :   init_new_variables
// args :   array, env list
// use :    init a new env variable
static int init_new_variable(char **array, list_t **head)
{
    list_t *new = malloc(sizeof(list_t));
    list_t *cur = NULL;

    if (!new)
        return 0;
    new->key = my_strdup(array[1]);
    if (!new->key) {
        my_free(new);
        return 0;
    }
    new->value = my_strdup(array[2]);
    new->next = NULL;
    if (!(*head)) {
        (*head) = new;
        return 0;
    }
    for (cur = (*head); cur->next; cur = cur->next);
    cur->next = new;
    return 0;
}

// name :   invalid_name
// args :   string
// use :    check if the name is correct according to the env standards
static int invalid_name(char *str)
{
    if ((str[0] > 'z' || str[0] < 'a') && (str[0] < 'A' ||
        str[0] > 'Z') && str[0] != '_') {
        mini_printf(2, "setenv: Variable name must begin with a letter.\n");
        return 1;
    }
    for (int i = 0; str[i] != '\0'; i++) {
        if ((str[i] > 'z' || str[i] < 'a') && (str[i] < 'A' || str[i] > 'Z') &&
            str[i] != '.' && str[i] != '_' && (str[i] < '0' || str[i] > '9')) {
            mini_printf(2, "setenv: Variable name must");
            mini_printf(2, " contain alphanumeric characters.\n");
            return 1;
            }
    }
    return 0;
}

// name :   replace
// args :   env list, array
// use :    replace the env value if the variable already exists
static int replace(list_t **head, char **array)
{
    int count = 0;

    for (list_t *tmp = *head; tmp; tmp = tmp->next)
        if (!my_strcmp(tmp->key, array[1])) {
            my_free(tmp->value);
            tmp->value = my_strdup(array[2]);
            count++;
        }
    return count;
}

// name :   setenv_error
// args :   array, shell main struct
// use :    setenv error_handling
static int setenv_error(char **array, shell_t *shell)
{
    int len = array_len((const void **) array);

    if (len > 3) {
        mini_printf(2, "setenv: Too many arguments.\n");
        shell->last_exit = 1;
        return 1;
    }
    if (len == 1) {
        print_env(shell->env);
        return 0;
    }
    return 1;
}

// name :   my_setenv
// args :   array, shell main struct
// use :    replace existing nodes, check the name of the variable and init it
int my_setenv(char **array, shell_t *shell)
{
    int len = array_len((const void **) array);

    if (len > 3 || len == 1) {
        shell->last_exit = setenv_error(array, shell);
        return shell->last_exit;
    }
    if (replace(&(shell->env), array) > 0) {
        shell->last_exit = 0;
        return shell->last_exit;
    }
    if (invalid_name(array[1])) {
        shell->last_exit = 1;
        return shell->last_exit;
    }
    shell->last_exit = init_new_variable(array, &(shell->env));
    return shell->last_exit;
}
