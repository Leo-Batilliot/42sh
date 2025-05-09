/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** parsing
*/

#include "line_edition.h"
#include <stddef.h>
#include <dirent.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

// name :   compare
// args :   string, completion struct
// use :    compare the string with the completion requirements
static int compare(char *str, completion_t *completion)
{
    int slen = my_strlen(completion->start);
    int elen = my_strlen(completion->end);

    if (slen + elen > my_strlen(str))
        return 1;
    if (slen && my_case_strncmp(str, completion->start, slen))
        return 1;
    if (elen && rev_case_strncmp(str, completion->end, elen))
        return 1;
    return 0;
}

// name :   add_completion_to_list
// args :   completion struct, name string
// use :    add the name to the list of completion
static int add_completion_to_list(completion_t *completion, char *name)
{
    list_t *node = malloc(sizeof(list_t));
    list_t *cur = NULL;

    if (!node || !name)
        return my_free(node);
    node->value = my_strdup(name);
    my_free(name);
    if (!node->value)
        return my_free(node);
    node->key = NULL;
    node->next = NULL;
    if (!completion->list) {
        completion->list = node;
    } else {
        for (cur = completion->list; cur->next; cur = cur->next);
        cur->next = node;
    }
    return 0;
}

// name :   parse_directory
// args :   directory name, completion struct
// use :    parse the directory to find the matching content
int parse_directory(char *name, completion_t *completion)
{
    DIR *dir;
    char full_path[4096];

    if (!name)
        return 0;
    dir = opendir(name);
    if (!dir)
        return 0;
    for (struct dirent *e = readdir(dir); e; e = readdir(dir)) {
        if (my_strlen(name) + my_strlen(e->d_name) > 4000)
            continue;
        snprintf(full_path, sizeof(full_path), "%s/%s", name, e->d_name);
        if (((completion->type == ELEMENTS) || !access(full_path, X_OK)) &&
            !compare(e->d_name, completion) && not_in(e->d_name, completion)
            && e->d_name[0] != '.')
            add_completion_to_list(completion,
                add_slash_to_dir(e->d_name, full_path));
    }
    closedir(dir);
    return 1;
}

// name :   fill_completion_list
// args :   completion struct, termios main struct
// use :    fill the completion list with corresponding names
int fill_completion_list(completion_t *completion, termios_t *termios)
{
    char **array = NULL;

    if (completion->directory)
        return parse_directory(completion->directory, completion);
    if (completion->type == COMMAND) {
        array = split_str(get_env_value("PATH", termios->env), ":");
        if (!array)
            return 1;
        for (int i = 0; array[i]; i++)
            parse_directory(array[i], completion);
        return free_array((void **)array);
    }
    return parse_directory(get_env_value("PWD", termios->env), completion);
}

// name :   get_str
// args :   string, index of cursor, position in the string, separators
// use :    get the string where the index is at according to separators
char *get_str(char *str, int index, int *position, char *separators)
{
    int len = 0;
    int word_start = 0;
    int i = 0;

    for (; str[i] != '\0' && i < index; i++)
        if (str_contain(separators, str[i]))
            word_start = i + 1;
    *position = i - word_start;
    str = str + word_start;
    for (; str[len] != '\0' && !str_contain(separators, str[len]); len++);
    return my_strndup(str, len);
}

// name :   type
// args :   a string, index of cursor, cmd separators, separators
// use :    find the type of element of the string where the cursor is at
int type(char *str, int index, char *cmd_seps, char *seps)
{
    int type = COMMAND;
    int writing = 0;

    for (int i = 0; str[i] != '\0' && i < index; i++) {
        if (!str_contain(cmd_seps, str[i]) && !str_contain(seps, str[i])) {
            writing = 1;
            continue;
        }
        if (writing && str_contain(seps, str[i]))
            type = ELEMENTS;
        if (str_contain(cmd_seps, str[i]))
            type = COMMAND;
        writing = 0;
    }
    return type;
}

// name :   get_directory
// args :   completion main struct
// use :    set the directory start and line according to the string content
int get_directory(completion_t *completion)
{
    int last_slash = 0;
    char *tmp = NULL;

    if (!str_contain(completion->start, '/'))
        return 0;
    for (int i = 0; completion->start[i] != '\0'; i++)
        if (completion->start[i] == '/')
            last_slash = i + 1;
    tmp = my_null_strdup(completion->start + last_slash);
    completion->directory = my_strndup(completion->start, last_slash);
    my_free(completion->start);
    completion->start = tmp;
    tmp = my_null_strdup(completion->line + last_slash);
    my_free(completion->line);
    completion->line = tmp;
    return 0;
}
