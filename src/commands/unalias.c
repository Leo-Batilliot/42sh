/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** unalias.c
*/


#include "shell.h"
#include <stddef.h>
#include <stdlib.h>

// name :   clear_all_alias
// args :   main shell struct
// use :    remove all aliases from the shell's alias list
int clear_all_alias(shell_t *shell)
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
    return 0;
}

// name :   remove_alias
// args :   current alias, previous alias, main shell struct
// use :    remove a specific alias from the shell's alias list
static void remove_alias(alias_t **current, alias_t **prev, shell_t *shell)
{
    if (*prev)
        (*prev)->next = (*current)->next;
    else
        shell->alias = (*current)->next;
    my_free((*current)->name);
    free_array((void **)(*current)->cmd);
    my_free(*current);
    *current = (*prev) ? (*prev)->next : shell->alias;
}

// name :   clear_alias
// args :   main shell struct, alias (name of the alias to remove)
// use :    find and remove a specific alias from the shell's alias list
static int clear_alias(shell_t *shell, char *alias)
{
    alias_t *current = shell->alias;
    alias_t *prev = NULL;
    int found = 0;

    while (current) {
        if (!my_strcmp(current->name, alias)) {
            found = 1;
            remove_alias(&current, &prev, shell);
            break;
        }
        prev = current;
        current = current->next;
    }
    return found;
}

// name :   handle_no_args
// args :   args
// use :    the case where no arguments are provided to the unalias command
static int handle_no_args(char **args)
{
    if (!args[1]) {
        mini_printf(2, "unalias: Too few arguments.\n");
        free_array((void **)args);
        return 1;
    }
    return 0;
}

// name :   handle_clear_all
// args :   args, main shell struct
// use :    handle the case where all aliases are to be removed
static int handle_clear_all(char **args, shell_t *shell)
{
    if (!my_strcmp(args[1], "*")) {
        clear_all_alias(shell);
        free_array((void **)args);
        return 0;
    }
    return -1;
}

// name :   handle_individual_aliases
// args :   args, main shell struct
// use :    removal of individual aliases from the shell's alias list
static int handle_individual_aliases(char **args, shell_t *shell)
{
    int found = 0;

    for (int i = 1; args[i]; i++) {
        found = clear_alias(shell, args[i]);
        if (!found) {
            mini_printf(2, "unalias: %s: alias not found.\n", args[i]);
            return 1;
        }
    }
    return 0;
}

// name :   unalias
// args :   array, main shell struct
// use :    remove one or all aliases from the shell's alias list
int unalias(char **array, shell_t *shell)
{
    char **args = simple_split_str(shell->line, "\t \n");
    int result;

    (void)array;
    if (!args)
        return 1;
    if (handle_no_args(args))
        return 1;
    result = handle_clear_all(args, shell);
    if (result != -1)
        return result;
    result = handle_individual_aliases(args, shell);
    free_array((void **)args);
    return result;
}
