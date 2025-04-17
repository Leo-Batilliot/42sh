/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-minishell1-gabin.wilson
** File description:
** my_setenv
*/

#include "my.h"

static int init_new_variable(char **array, linked_list_t **head)
{
    linked_list_t *new = malloc(sizeof(linked_list_t));
    linked_list_t *cur = NULL;

    if (!new)
        return 0;
    new->key = my_strdup(array[1]);
    if (!new->key) {
        free(new);
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

static int invalid_name(char *str)
{
    if ((str[0] > 'z' || str[0] < 'a') && (str[0] < 'A' ||
        str[0] > 'Z') && str[0] != '_') {
        fprintf(stderr, "setenv: Variable name must begin with a letter.\n");
        return 1;
    }
    for (int i = 0; str[i] != '\0'; i++) {
        if ((str[i] > 'z' || str[i] < 'a') && (str[i] < 'A' || str[i] > 'Z') &&
            str[i] != '.' && str[i] != '_' && (str[i] < '0' || str[i] > '9')) {
            fprintf(stderr, "setenv: Variable name must");
            fprintf(stderr, " contain alphanumeric characters.\n");
            return 1;
            }
    }
    return 0;
}

static int replace(linked_list_t **head, char **array)
{
    int count = 0;

    for (linked_list_t *tmp = *head; tmp; tmp = tmp->next)
        if (!my_strcmp(tmp->key, array[1])) {
            my_free(tmp->value);
            tmp->value = my_strdup(array[2]);
            count++;
        }
    return count;
}

static int setenv_error(linked_list_t **head, char **array, shell_t *shell)
{
    int len = array_len((const void **) array);

    if (len > 3) {
        fprintf(stderr, "setenv: Too many arguments.\n");
        shell->last_exit = 1;
        return 1;
    }
    if (len == 1) {
        print_env(head);
        return 0;
    }
    return 1;
}

int my_setenv(linked_list_t **head, char **array, shell_t *shell)
{
    int len = array_len((const void **) array);

    if (len > 3 || len == 1) {
        shell->last_exit = setenv_error(head, array, shell);
        return shell->last_exit;
    }
    if (replace(head, array) > 0) {
        shell->last_exit = 0;
        return shell->last_exit;
    }
    if (invalid_name(array[1])) {
        shell->last_exit = 1;
        return shell->last_exit;
    }
    shell->last_exit = init_new_variable(array, head);
    return shell->last_exit;
}
