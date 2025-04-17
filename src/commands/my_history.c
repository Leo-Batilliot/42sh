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

static int is_last_command_same(info_shell_t *shell_i, char *cmd)
{
    history_t *current = shell_i->head;

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
            return ERROR;
        sprintf(node->full_line, "%s%i  %s  %s",
        put_spaces(index), node->index, node->time, node->cmd);
    } else {
        node->full_line = malloc(sizeof(char) * strlen(cmd) + 1);
        if (!node->full_line)
            return ERROR;
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
    if (create_history_line(new_node, index, cmd, status) == ERROR)
        return NULL;
    new_node->next = NULL;
    return new_node;
}

static int append_history_node(info_shell_t *shell_i, history_t *new_node)
{
    history_t *current = NULL;

    if (shell_i->head == NULL) {
        shell_i->head = new_node;
    } else {
        current = shell_i->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
    shell_i->count++;
    return 0;
}

int add_node_to_history(info_shell_t *shell_i, char *cmd, bool status)
{
    history_t *new_node = create_history_node(shell_i->count + 1, cmd, status);

    if (new_node == NULL)
        return ERROR;
    return append_history_node(shell_i, new_node);
}

void add_to_file(info_shell_t *shell_i)
{
    FILE *fp = fopen("history", "w");
    history_t *current = shell_i->head;

    if (!fp)
        return;
    while (current) {
        fprintf(fp, "%s", current->full_line);
        current = current->next;
    }
    fclose(fp);
}

int add_to_history(info_shell_t *shell_i, char *cmd)
{
    int value = 0;

    if (is_last_command_same(shell_i, cmd)) {
        return 0;
    }
    value = add_node_to_history(shell_i, cmd, true);
    if (value == ERROR)
        return ERROR;
    add_to_file(shell_i);
    return 0;
}

int my_history(char *cmd)
{
    FILE *fp = fopen("history", "r");
    char *line = NULL;
    size_t len = 0;

    if (!fp)
        return ERROR;
    if (strcmp("history", cmd) == 0) {
        while (getline(&line, &len, fp) != -1) {
            printf("%s", line);
        }
        return 2;
    }
    fclose(fp);
    return 0;
}
