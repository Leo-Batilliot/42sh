/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** functions_delim
*/

#include "shell.h"
#include <stddef.h>

static const char *array[] = {"<", ">", "|", "&", NULL};

static int get_pos(int len, const char *str)
{
    int pos = len;

    while (str[pos] == '<' || str[pos] == '>')
        pos++;
    return pos;
}

static int is_array(const char *str)
{
    int len = 0;

    for (int i = 0; array[i]; i++) {
        len = my_strlen(array[i]);
        if (!my_strncmp(str, array[i], len))
            return get_pos(len, str);
    }
    return 0;
}

static int update_in_word(const char *string,
    int update[2], int *in_word)
{
    int len_array = is_array(&string[update[0]]);

    if (len_array > 0) {
        update[1]++;
        update[0] += len_array - 1;
        *in_word = 0;
        return 1;
    }
    if (is_delim(string[update[0]])) {
        update[1]++;
        in_word = 0;
    }
    return 0;
}

int count_word(const char *string, char *operator)
{
    int in_word = 0;
    int update[2] = {0, 0};

    for (; string[update[0]]; update[0]++) {
        if (update_in_word(string, update, &in_word))
            continue;
        if (!is_separator(string[update[0]], operator)
        && !in_word
        && !is_delim(string[update[0]])) {
            update[1]++;
            in_word = 1;
        }
        if (is_separator(string[update[0]], operator)
        && !is_delim(string[update[0]]) && in_word)
            in_word = 0;
    }
    return update[1];
}
