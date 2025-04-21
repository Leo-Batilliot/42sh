/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** init
*/
#include "my.h"

static int get_count(args_t *new, char **array)
{
    for (int i = 0; array[i]; i++) {
        if (!my_strcmp(";", array[i]) || !my_strcmp("|", array[i]))
            break;
        if (!my_strcmp("<", array[i])
            || !my_strcmp(">", array[i])
            || !my_strcmp(">>", array[i])
            || !my_strcmp("<<", array[i]))
            new->count_red++;
    }
    if (new->count_red > 0) {
        new->redir = malloc(sizeof(redirect_t) * new->count_red);
        if (!new->redir)
            return 1;
    }
    return 0;
}

static int count_args_until_sep(char **array)
{
    int count = 0;

    for (int i = 0; array[i]; i++) {
        if (!my_strcmp(array[i], ";") || !my_strcmp(array[i], "|"))
            break;
        if (!is_operator(array[i]))
            count++;
    }
    return count;
}

args_t *init_cmd(char **array)
{
    args_t *new = NULL;
    int count_args = count_args_until_sep(array);

    new = malloc(sizeof(args_t));
    if (!new)
        return NULL;
    new->args = malloc(sizeof(char *) * (count_args + 1));
    if (!new->args)
        return NULL;
    for (int i = 0; i <= count_args; i++)
        new->args[i] = NULL;
    new->is_pipe = 0;
    new->next = NULL;
    new->redir = NULL;
    new->count_red = 0;
    if (get_count(new, array))
        return NULL;
    return new;
}

static linked_list_t *add_to_list(
    linked_list_t *head, linked_list_t *node)
{
    linked_list_t *cur = NULL;

    if (!head) {
        head = node;
    } else {
        cur = head;
        while (cur->next)
            cur = cur->next;
        cur->next = node;
    }
    return head;
}

static linked_list_t *init_node(char *ope, char **env, int i)
{
    linked_list_t *node = malloc(sizeof(linked_list_t));

    if (!node)
        return NULL;
    node->key = my_strdup(env[i]);
    node->value = my_strdup(ope + 1);
    if (!node->key || !node->value) {
        my_free(node->value);
        my_free(node->key);
        my_free(node);
        return NULL;
    }
    node->next = NULL;
    return node;
}

static linked_list_t *my_parse_env(char **env)
{
    char *ope = NULL;
    linked_list_t *head = NULL;
    linked_list_t *node = NULL;

    for (int i = 0; env[i]; i++) {
        ope = my_strchr(env[i], '=');
        if (!ope)
            return NULL;
        *ope = '\0';
        node = init_node(ope, env, i);
        if (!node)
            return NULL;
        *ope = '=';
        head = add_to_list(head, node);
    }
    return head;
}

static shell_t *alloc_shell(void)
{
    shell_t *shell = malloc(sizeof(shell_t));

    if (!shell)
        return NULL;
    shell->path = NULL;
    shell->line = NULL;
    shell->save_old = NULL;
    shell->last_exit = 0;
    shell->size = 0;
    shell->res = 0;
    shell->prev = 0;
    shell->alias = NULL;
    shell->head = NULL;
    shell->count = 0;
    shell->list = NULL;
    shell->env_cpy = NULL;
    return shell;
}

shell_t *init_shell(char **env)
{
    shell_t *shell = alloc_shell();

    if (!shell)
        return NULL;
    shell->env_cpy = my_env_cpy(env);
    if (!shell->env_cpy)
        return NULL;
    shell->list = init_list();
    if (!shell->list)
        return NULL;
    return shell;
}

linked_list_t *init_env(char **env_cpy)
{
    linked_list_t *head = NULL;

    if (!env_cpy)
        return NULL;
    head = my_parse_env(env_cpy);
    return head;
}

list_t *init_list(void)
{
    list_t *list = malloc(sizeof(list_t));

    if (!list)
        return NULL;
    list->head = NULL;
    return list;
}
