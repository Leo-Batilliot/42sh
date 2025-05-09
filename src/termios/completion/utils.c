/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** utils
*/

#include "line_edition.h"
#include <sys/stat.h>
#include <stddef.h>
#include <stdlib.h>

// name :   not_in
// args :   a string, completion struct
// use :    return 0 if the string doesnt exist in the completion list
int not_in(char *name, completion_t *completion)
{
    for (list_t *cur = completion->list; cur; cur = cur->next)
        if (!my_strcmp(cur->value, name))
            return 0;
    return 1;
}

// name :   add_slash_to_dir
// args :   name, full path to element
// use :    will add a '/' at the end of a directory name if it is one
char *add_slash_to_dir(char *name, char *full_path)
{
    struct stat st;
    char *copy;
    int len = my_strlen(name);

    if (stat(full_path, &st) == 0 && S_ISDIR(st.st_mode)) {
        copy = malloc(sizeof(char) * (len + 2));
        if (!copy)
            return my_strdup(name);
        copy = my_strcpy(copy, name);
        copy[len] = '/';
        copy[len + 1] = '\0';
        return copy;
    }
    return my_strdup(name);
}

// name :   str_contain
// args :   a string, a character
int str_contain(char *str, char c)
{
    if (!str)
        return 0;
    for (int i = 0; str[i] != '\0'; i++)
        if (str[i] == c)
            return 1;
    return 0;
}

// name :   get_max_length
// args :   completion main struct
// use :    returns the length of the longest element in the completion list
int get_max_length(completion_t *completion)
{
    int max_len = 0;
    list_t *node = completion->list;
    int len = 0;

    for (int i = 0; i < completion->len; i++) {
        len = my_strlen(node->value);
        if (len > max_len)
            max_len = len;
        node = node->next;
    }
    return max_len + 2;
}

// name :   replace
// args :   termios struct, completion struct
// use :    replace the current termios->line with the auto completed one
int replace(termios_t *termios, completion_t *completion)
{
    int len = 0;
    char *tab[5] = {completion->before, completion->directory,
        completion->line, completion->after, NULL};

    for (int i = 0; i < 4; i++) {
        if (len + my_strlen(tab[i]) > BUFFER_SIZE)
            return 1;
        termios->line = strcpy_from(termios->line, tab[i], len);
        len += my_strlen(tab[i]);
    }
    termios->pos = len;
    return 1;
}
