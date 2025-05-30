/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-minishell1-gabin.wilson
** File description:
** my_unsetenv
*/

#include "shell.h"
#include "stddef.h"

// name :   delete_node
// args :   env list, current node, previous node
// use :    delete given node
static int delete_node(list_t **head, list_t **tmp,
    list_t **prev)
{
    list_t *next = (*tmp)->next;

    if (!(*prev))
        *head = (*tmp)->next;
    else
        (*prev)->next = next;
    if ((*tmp)->key)
        my_free((*tmp)->key);
    if ((*tmp)->value)
        my_free((*tmp)->value);
    my_free(*tmp);
    (*tmp) = next;
    return 0;
}

// name :   check_key
// args :   previous node, current node, list, array
// use :    compares array's names to the node and delete it if needed
static int check_key(list_t **prev, list_t **tmp,
    list_t **head, char **array)
{
    for (int i = 1; array[i]; i++)
        if (!my_strcmp(array[i], (*tmp)->key))
            return delete_node(head, tmp, prev);
    (*prev) = (*tmp);
    return 0;
}

// name :   my_unsetenv
// args :   array, shell main struct
// use :    loops through the env list to delete given nodes
int my_unsetenv(char **array, shell_t *shell)
{
    list_t *prev = NULL;
    list_t *next = NULL;

    if (!array[1]) {
        mini_printf(2, "unsetenv: Too few arguments.\n");
        shell->last_exit = 1;
        return 1;
    }
    if (!shell->env) {
        shell->last_exit = 1;
        return 1;
    }
    for (list_t *tmp = shell->env; tmp; tmp = next) {
        next = tmp->next;
        check_key(&prev, &tmp, &(shell->env), array);
    }
    return 2;
}
