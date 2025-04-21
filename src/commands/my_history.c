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
    char *buffer = malloc(sizeof(char) * 6);

    sprintf(buffer, "%02d:%02d", local->tm_hour, local->tm_min);
    return buffer;
}

static int is_last_command_same(shell_t *shell, char *cmd)
{
    history_t *current = shell->head;

    while (current != NULL && current->next != NULL) {
        current = current->next;
    }
    if (current != NULL && strcmp(current->cmd, cmd) == 0) {
        free(current->time);
        current->time = get_current_time();
        return 1;
    }
    return 0;
}

static int create_history_line(history_t *node, int index,
    char *cmd, bool status)
{
    if (status == true) {
        node->full_line = malloc(sizeof(char) *
        strlen(node->time) + strlen(node->cmd) + 10);
        if (!node->full_line)
            return 1;
        sprintf(node->full_line, "%s%i  %s  %s",
        put_spaces(index), node->index, node->time, node->cmd);
    } else {
        node->full_line = malloc(sizeof(char) * strlen(cmd) + 1);
        if (!node->full_line)
            return 1;
        sprintf(node->full_line, "%s", cmd);
    }
    return 0;
}

static history_t *create_history_node(int index, char *cmd, bool status)
{
    history_t *new_node = malloc(sizeof(history_t));

    if (new_node == NULL || strcmp("\n", cmd) == 0)
        return NULL;
    if (status == true) {
        new_node->index = index;
        new_node->time = get_current_time();
    }
    new_node->cmd = malloc(strlen(cmd) + 1);
    if (new_node->cmd == NULL)
        return NULL;
    strcpy(new_node->cmd, cmd);
    if (create_history_line(new_node, index, cmd, status) == 1)
        return NULL;
    new_node->next = NULL;
    return new_node;
}

static int append_history_node(shell_t *shell, history_t *new_node)
{
    history_t *current = NULL;

    if (shell->head == NULL) {
        shell->head = new_node;
    } else {
        current = shell->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
    shell->count++;
    return 0;
}

int add_node_to_history(shell_t *shell, char *cmd, bool status)
{
    history_t *new_node = create_history_node(shell->count + 1, cmd, status);

    if (new_node == NULL)
        return 1;
    return append_history_node(shell, new_node);
}

int add_to_history(shell_t *shell, char *cmd)
{
    int value = 0;

    if (is_last_command_same(shell, cmd))
        return 0;
    value = add_node_to_history(shell, cmd, true);
    if (value == 1)
        return 1;
    write_history(shell);
    return 0;
}

int my_history(char **array, linked_list_t **head, shell_t *shell)
{
    (void)array;
    (void)head;
    while (shell->head != NULL) {
        printf("%s", shell->head->full_line);
        shell->head = shell->head->next;
    }
    return 0;
}
