/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** my_history.c
*/

#include "my.h"

static char *get_current_time(void)
{
    time_t cur_time = time(NULL);
    struct tm *local = localtime(&cur_time);
    char *buffer = malloc(sizeof(char) * 7);

    if (!buffer)
        return NULL;
    sprintf(buffer, "%02d:%02d", local->tm_hour, local->tm_min);
    return buffer;
}

static int is_last_command_same(shell_t *shell, char *cmd)
{
    history_t *current = shell->history;

    while (current != NULL && current->next != NULL) {
        current = current->next;
    }
    if (current != NULL && strcmp(current->cmd, cmd) == 0) {
        free(current->time);
        current->time = get_current_time();
        if (!current->time)
            return -1;
        return 1;
    }
    return 0;
}

static history_t *create_history_node(char *cmd)
{
    history_t *new_node = malloc(sizeof(history_t));

    if (new_node == NULL || !strcmp("\n", cmd))
        return NULL;
    new_node->time = get_current_time();
    if (!new_node->time)
        return NULL;
    new_node->cmd = strdup(cmd);
    if (new_node->cmd == NULL)
        return NULL;
    new_node->next = NULL;
    return new_node;
}

static int append_history_node(shell_t *shell, history_t *new_node)
{
    history_t *current = NULL;

    if (shell->history == NULL) {
        shell->history = new_node;
    } else {
        current = shell->history;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
    return 0;
}

int add_node_to_history(shell_t *shell, char *cmd)
{
    history_t *new_node = create_history_node(cmd);

    if (new_node == NULL)
        return 1;
    return append_history_node(shell, new_node);
}

int add_to_history(shell_t *shell, char *cmd)
{
    int value = 0;

    value = is_last_command_same(shell, cmd);
    if (value)
        return (value == 1) ? 0 : 1;
    if (add_node_to_history(shell, cmd))
        return 1;
    return 0;
}

int my_history(char **array, shell_t *shell)
{
    char *spaces = NULL;
    int last_index = 1;
    int i = 1;

    (void)array;
    for (history_t *tmp = shell->history; tmp; tmp = tmp->next)
        last_index++;
    for (history_t *cur = shell->history; cur; cur = cur->next) {
        spaces = put_spaces(i, last_index);
        if (!spaces)
            return 1;
        printf("%s%i  %s  %s", spaces, i, cur->time, cur->cmd);
        i++;
    }
    return 0;
}
