/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** history
*/
#include "line_edition.h"

void reset_termios_history(termios_t *termios, int *history)
{
    (*history) = 0;
    my_free(termios->history_line);
    termios->history_line = NULL;
    termios->history_index = 0;
}

static char *get_previous_command(termios_t *termios, int *index)
{
    char *cmp = termios->history_line;
    char *res = NULL;
    int count = 1;

    (*index)++;
    for (history_t *cur = termios->history; cur; cur = cur->next) {
        if ((count < termios->history_index || !termios->history_index) &&
            (!my_strncmp(cur->cmd, cmp, termios->history_pos) || !cmp)) {
            res = cur->cmd;
            (*index) = count;
        }
        count++;
    }
    return res;
}

static char *get_next_command(termios_t *termios, int *index)
{
    char *res = termios->history_line;
    int count = 1;

    if (!termios->history_line)
        return NULL;
    for (history_t *cur = termios->history; cur; cur = cur->next) {
        if (count > termios->history_index && termios->history_index != 0 &&
            !my_strncmp(cur->cmd, termios->history_line,
            termios->history_pos)) {
            (*index) = count;
            return cur->cmd;
        }
        count++;
    }
    (*index) = 0;
    return res;
}

void replace_current_line(termios_t *termios, char *str)
{
    int i = 0;

    for (; i < BUFFER_SIZE && str[i] != '\0'; i++)
        termios->line[i] = str[i];
    termios->line[i] = '\0';
    termios->pos = my_strlen(termios->line);
}

static char *my_strdup2(char *str)
{
    char *res = NULL;

    if (!my_strlen(str)) {
        res = malloc(sizeof(char));
        if (!res)
            return NULL;
        res[0] = '\0';
        return res;
    }
    return my_strdup(str);
}

int move_history(termios_t *termios, int option)
{
    char *res = NULL;
    int index = 0;

    if (!termios->history_line) {
        termios->history_line = my_strdup2(termios->line);
        termios->history_pos = termios->pos;
    }
    if (option)
        res = get_previous_command(termios, &index);
    else
        res = get_next_command(termios, &index);
    if (!res)
        return 2;
    termios->history_index = index;
    replace_current_line(termios, res);
    return 2;
}
