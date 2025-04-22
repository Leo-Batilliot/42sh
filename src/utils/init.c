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

static list_t *add_to_list(
    list_t *head, list_t *node)
{
    list_t *cur = NULL;

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

static list_t *init_node(char *ope, char **env, int i)
{
    list_t *node = malloc(sizeof(list_t));

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

static list_t *my_parse_env(char **env)
{
    char *ope = NULL;
    list_t *head = NULL;
    list_t *node = NULL;

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

static void *init_shell_values(shell_t *shell, char **env)
{
    shell->path = NULL;
    shell->last_exit = 0;
    shell->prev = 0;
    shell->alias = NULL;
    shell->history = NULL;
    shell->args = NULL;
    shell->previous_pwd = NULL;
    shell->env_cpy = my_env_cpy(env);
    if (!shell->env_cpy)
        return NULL;
    shell->prompt_color = NULL;
    return shell;
}

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

list_t *init_env(char **env_cpy)
{
    list_t *head = NULL;

    if (!env_cpy)
        return NULL;
    head = my_parse_env(env_cpy);
    return head;
}
