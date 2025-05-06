/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** init
*/

#include "shell.h"
#include <stddef.h>
#include <stdlib.h>

// name :   add_to_list
// args :   list head, node
// use :    add node to the end of list
static list_t *add_to_list(list_t *head, list_t *node)
{
    list_t *cur = NULL;

    if (!head) {
        head = node;
    } else {
        for (cur = head; cur->next; cur = cur->next);
        cur->next = node;
    }
    return head;
}

// name :   init_node
// args :   value, env array, index
// use :    init a new env variable using the env array
static list_t *init_node(char *value, char **env, int i)
{
    list_t *node = malloc(sizeof(list_t));

    if (!node)
        return NULL;
    node->key = my_strdup(env[i]);
    node->value = my_strdup(value + 1);
    if (!node->key || !node->value) {
        my_free(node->value);
        my_free(node->key);
        my_free(node);
        return NULL;
    }
    node->next = NULL;
    return node;
}

// name :   my_parse_env
// args :   env array
// use : parse the env array and init a linked list with it
static list_t *my_parse_env(char **env)
{
    char *value = NULL;
    list_t *head = NULL;
    list_t *node = NULL;

    for (int i = 0; env[i]; i++) {
        value = my_strchr(env[i], '=');
        if (!value)
            return NULL;
        *value = '\0';
        node = init_node(value, env, i);
        if (!node)
            return NULL;
        *value = '=';
        head = add_to_list(head, node);
    }
    return head;
}

// name :   init_shell_values
// args :   main shell struct, env array
// use :    S.E
static void *init_shell_values(shell_t *shell, char **env)
{
    shell->path = NULL;
    shell->line = NULL;
    shell->last_exit = 0;
    shell->param = 0;
    shell->prev = 0;
    shell->alias = NULL;
    shell->history = NULL;
    shell->previous_pwd = NULL;
    shell->env_cpy = my_env_cpy(env);
    if (!shell->env_cpy)
        return NULL;
    shell->prompt_color = NULL;
    shell->local_vars = NULL;
    return shell;
}

// name :   init_shell
// args :   env array
// use :    S.E
shell_t *init_shell(char **env)
{
    shell_t *shell = malloc(sizeof(shell_t));

    if (!shell)
        return NULL;
    init_shell_values(shell, env);
    shell->prompt_color = my_strdup("\033[0m");
    if (!shell->prompt_color)
        return NULL;
    return shell;
}

// name :   init_env
// args :   env array
// use :    use the env copy to create an env linked list
list_t *init_env(char **env_cpy)
{
    list_t *head = NULL;

    if (!env_cpy || !env_cpy[0])
        env_cpy = create_default_env(env_cpy);
    if (!env_cpy)
        return NULL;
    head = my_parse_env(env_cpy);
    return head;
}
