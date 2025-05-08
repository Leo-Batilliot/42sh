/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** unalias.c
*/

#include "shell.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

static void clear_all_alias(shell_t *shell)
{
    alias_t *current = shell->alias;
    alias_t *next;

    while (current) {
        next = current->next;
        my_free(current->name);
        free_array((void **)current->cmd);
        my_free(current);
        current = next;
    }
    shell->alias = NULL;
}

static int remove_single_alias(shell_t *shell, char *alias_name)
{
    alias_t *current = shell->alias;
    alias_t *prev = NULL;

    while (current) {
        if (!my_strcmp(current->name, alias_name)) {
            if (prev)
                prev->next = current->next;
            else
                shell->alias = current->next;
            
            my_free(current->name);
            free_array((void **)current->cmd);
            my_free(current);
            return 1;
        }
        prev = current;
        current = current->next;
    }
    return 0;
}

int unalias(char **array, shell_t *shell)
{
    if (!array[1]) {
        mini_printf(2, "unalias: Too few arguments.\n");
        return 1;
    }

    // Handle 'unalias *' case
    if (!my_strcmp(array[1], "*")) {
        clear_all_alias(shell);
        return 0;
    }

    // Handle multiple aliases to remove
    int ret = 0;
    for (int i = 1; array[i]; i++) {
        printf("%s\n", array[i]);
        if (!remove_single_alias(shell, array[i])) {
            mini_printf(2, "unalias: %s: alias not found.\n", array[i]);
            ret = 1;
        }
    }

    return ret;
}