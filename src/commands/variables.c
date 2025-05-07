/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** variables.c
*/

#include "shell.h"
#include <stdlib.h>
#include <stdio.h>

// name:    init_set_value
// args:    new node in set list, name, value
// use:     init value in new node set list
static int init_set_value(list_t *new_node, char *name, char *value)
{
    new_node->key = my_strdup(name);
    new_node->value = my_strdup(value);
    new_node->next = NULL;
    if (!new_node->key || !new_node->value) {
        my_free(new_node->key);
        my_free(new_node->value);
        my_free(new_node);
        return 1;
    }
    return 0;
}

// name:    add_set_node
// args:    shell main struct, name, value
// use:     add node to end of list set
int add_set_node(shell_t *shell, char *name, char *value)
{
    list_t *new_node = malloc(sizeof(list_t));
    list_t *last = shell->local_vars;

    if (!new_node)
        return 1;
    if (init_set_value(new_node, name, value))
        return 1;
    if (!last)
        shell->local_vars = new_node;
    else {
        for (last = shell->local_vars; last->next; last = last->next);
        last->next = new_node;
    }
    return 0;
}

// name:    print_set
// args:    args array, list set, shell main struct
// use:     print set
static int print_set(shell_t *shell, list_t *node, char **args)
{
    if (!args || !args[1]) {
        for (node = shell->local_vars; node; node = node->next) {
            mini_printf(1, "%s\t%s\n", node->key, node->value);
        }
        return 1;
    }
    return 0;
}

// name:    get_value
// args:    args array
// use:     get set value
static char *get_value(char **args)
{
    if (args[2] == NULL)
        return "";
    if (my_strcmp(args[2], "=") == 0) {
        if (args[3] != NULL)
            return args[3];
        else
            return "";
    } else
        return "";
    return args[2];
}

//name:    handle_ignoreeof
//args:    shell main struct, args array
//use:     handle ignoreeof special variable
static void handle_ignoreeof(shell_t *shell, char **args)
{
    if (!my_strcmp(args[1], "ignoreeof")) {
        shell->ignoreeof = -1;
        if (args[2] && !my_strcmp(args[2], "=") && args[3])
            shell->ignoreeof = atoi(args[3]);
    }
}

// name:    set_local_var
// args:    args array, shell main struct
// use:     set or modify a local variable
int set(char **args, shell_t *shell)
{
    list_t *node = NULL;
    char *name = NULL;
    char *value = NULL;

    if (print_set(shell, node, args))
        return 0;
    handle_ignoreeof(shell, args);
    name = args[1];
    value = get_value(args);
    for (node = shell->local_vars; node; node = node->next) {
        if (!my_strcmp(node->key, name)) {
            my_free(node->value);
            node->value = my_strdup(value);
            return 0;
        }
    }
    if (add_set_node(shell, name, value))
        return 1;
    return 0;
}

// name:    remove_var_node
// args:    shell, previous node, curent node
// use:     remove a variable node from the list and free its memory
static int remove_var_node(shell_t *shell, list_t *prev, list_t *cur)
{
    if (prev)
        prev->next = cur->next;
    else
        shell->local_vars = cur->next;
    my_free(cur->key);
    my_free(cur->value);
    my_free(cur);
    return 0;
}

// name:    unset_loop
// args:    return, args array, shell main struct
// use:     loop to remove node
int unset_loop(int ret, char *arg, shell_t *shell)
{
    list_t *prev = NULL;
    list_t *cur = NULL;

    prev = NULL;
    for (cur = shell->local_vars; cur; cur = cur->next) {
        if (!my_strcmp(cur->key, arg)) {
            remove_var_node(shell, prev, cur);
            ret = 0;
            break;
        }
        prev = cur;
    }
    if (!cur) {
        mini_printf(2, "unset: no such variable: %s\n", arg);
        ret = 1;
    }
    return ret;
}

// name:    unset
// args:    args array, shell main struct
// use:     remove one or more local variables
int unset(char **args, shell_t *shell)
{
    int ret = 0;

    if (!args || !args[1]) {
        mini_printf(2, "unset: missing argument\n");
        shell->last_exit = 1;
        return 1;
    }
    if (!my_strcmp(args[1], "ignoreeof"))
    shell->ignoreeof = 0;
    for (int i = 1; args[i]; i++) {
        if (!my_strcmp(args[i], "ignoreeof"))
            shell->ignoreeof = 0;
        ret = unset_loop(ret, args[i], shell);
    }
    shell->last_exit = ret;
    return ret;
}
