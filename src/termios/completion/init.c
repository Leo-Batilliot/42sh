/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** init
*/

#include "line_edition.h"
#include <stddef.h>
#include <stdlib.h>

// name :   free_completion
// args :   auto completion struct
// use :    S.E
int free_completion(completion_t *completion)
{
    if (!completion)
        return 0;
    my_free(completion->directory);
    my_free(completion->end);
    my_free(completion->start);
    my_free(completion->line);
    my_free(completion->after);
    my_free(completion->before);
    free_list(completion->list);
    my_free(completion);
    return 0;
}

// name :   special_completion
// args :   termios struct, completion struct, int error (too many completions)
// use :    print all completions if too many and auto complete if only one
int special_completion(termios_t *termios, completion_t *completion, int error)
{
    if (completion->len == 1) {
        completion->index = 0;
        refresh_completion_line(completion);
        replace(termios, completion);
        return 1;
    }
    if (error) {
        display_completion_options(completion);
        return 1;
    }
    return 0;
}

// name :   init_completion_list
// args :   auto completion struct, termios main struct
// use :    create a list of elements that could complete the line
int init_completion_list(completion_t *completion, termios_t *termios)
{
    int pos = 0;

    completion->line = get_str(
        termios->line, termios->pos, &pos, "<>|&() \t\n;");
    if (completion->line) {
        completion->end = my_null_strdup(completion->line + pos);
        completion->start = my_strndup(completion->line, pos);
    }
    completion->before = my_strndup(termios->line, termios->pos - pos);
    completion->after = my_strdup(
        termios->line + termios->pos - pos + my_strlen(completion->line));
    completion->type = type(termios->line, termios->pos, "|&(;", " \t\n)<>");
    get_directory(completion);
    return fill_completion_list(completion, termios);
}

// name :   init_completion_variables
// args :   auto completion struct
// use :    S.E
void init_completion_variables(completion_t *completion)
{
    completion->directory = NULL;
    completion->end = NULL;
    completion->start = NULL;
    completion->before = NULL;
    completion->after = NULL;
    completion->max_len = 0;
    completion->rows = 0;
    completion->cols = 0;
    completion->index = -2;
    completion->len = 0;
    completion->line = NULL;
    completion->list = NULL;
    completion->start = NULL;
    completion->type = 0;
    completion->printed = 0;
}

// name :   init_completion
// args :   termios main struct
// use :    S.E
completion_t *init_completion(termios_t *termios)
{
    int error = 0;
    completion_t *completion = malloc(sizeof(completion_t));

    if (!completion)
        return NULL;
    init_completion_variables(completion);
    init_completion_list(completion, termios);
    if (!completion->list) {
        free_completion(completion);
        return NULL;
    }
    for (list_t *node = completion->list; node; node = node->next)
        completion->len++;
    completion->max_len = get_max_length(completion);
    error = refresh_window_size(completion);
    if (special_completion(termios, completion, error)) {
        free_completion(completion);
        return NULL;
    }
    return completion;
}
