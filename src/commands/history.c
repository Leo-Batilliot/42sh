/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** my_history.c
*/

#include "shell.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

// name :   get_current_time
// args :   N.A
// use :    S.E
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

// name :   is_last_command_same
// args :   shell main struct, cmd string
// use :    check if the previous cmd == cmd and doesnt add to history if so
static int is_last_command_same(shell_t *shell, char *cmd)
{
    history_t *current = shell->history;

    for (; current && current->next; current = current->next);
    if (current && !my_strcmp(current->cmd, cmd)) {
        my_free(current->time);
        current->time = get_current_time();
        if (!current->time)
            return -1;
        return 1;
    }
    return 0;
}

// name :   init_history_node
// args :   time string, cmd string
// use :    creates a new history node and return it
static history_t *init_history_node(char *time, char *cmd)
{
    history_t *new_node = malloc(sizeof(history_t));

    if (!new_node || !my_strcmp("\n", cmd))
        return NULL;
    new_node->time = my_strdup(time);
    if (!new_node->time)
        new_node->time = get_current_time();
    if (!new_node->time)
        return NULL;
    new_node->cmd = my_strdup(cmd);
    if (!new_node->cmd)
        return NULL;
    new_node->next = NULL;
    return new_node;
}

// name :   append_history_node
// args :   shell main struct, new history node
// use :    add a history node to the list
static int append_history_node(shell_t *shell, history_t *new_node)
{
    history_t *current = NULL;

    if (shell->history == NULL) {
        shell->history = new_node;
    } else {
        for (current = shell->history; current->next; current = current->next);
        current->next = new_node;
    }
    return 0;
}

// name :   add_node_to_history
// args :   shell main struct, time string, cmd string
// use :    init a new node and add it to the list
int add_node_to_history(shell_t *shell, char *time, char *cmd)
{
    history_t *new_node;

    if (!cmd)
        return 1;
    new_node = init_history_node(time, cmd);
    if (!new_node)
        return 1;
    return append_history_node(shell, new_node);
}

// name :   add_to_history
// args :   shell main struct, cmd string
// use :    check if the last command was the same before adding to history
int add_to_history(shell_t *shell, char *cmd)
{
    int value = 0;

    if (cmd[my_strlen(cmd) - 1] == '\n')
        cmd[my_strlen(cmd) - 1] = '\0';
    value = is_last_command_same(shell, cmd);
    if (value)
        return (value == 1) ? 0 : 1;
    if (add_node_to_history(shell, NULL, cmd))
        return 1;
    return 0;
}

// name :   my_history
// args :   array, shell main struct
// use :    print the history list
int my_history(char **array, shell_t *shell)
{
    int last_index = 1;
    int i = 1;
    int spaces = 0;

    (void)array;
    for (history_t *tmp = shell->history; tmp; tmp = tmp->next)
        last_index++;
    for (history_t *cur = shell->history; cur; cur = cur->next) {
        spaces = spaces_count(i, last_index - 1);
        for (int s = 0; s < spaces; s++)
            printf(" ");
        printf("%i  %s  %s\n", i, cur->time, cur->cmd);
        i++;
    }
    return 0;
}
