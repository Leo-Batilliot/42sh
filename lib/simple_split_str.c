/*
** EPITECH PROJECT, 2024
** str to word array
** File description:
** task 04
*/

#include "shell.h"
#include <stddef.h>
#include <stdlib.h>

static int is_a_delim(char *str, char *delim, int *i)
{
    for (int y = 0; delim[y] != '\0'; y++)
        if (delim[y] == str[*i]) {
            i++;
            return 1;
        }
    return 0;
}

int count_words(char *str, char *delim)
{
    int count = 0;
    int letter_count = 0;

    for (int i = 0; i < my_strlen(str); i++) {
        letter_count = 0;
        for (; !is_a_delim(str, delim, &i) && i < my_strlen(str); i++)
            letter_count++;
        if (letter_count != 0)
            count++;
    }
    return count;
}

char **words_to_array(char **res, char *str, char *delim)
{
    int count = 0;
    int letter_count = 0;

    for (int i = 0; i < my_strlen(str); i++) {
        letter_count = 0;
        for (; !is_a_delim(str, delim, &i) && str[i] != '\0'; i++)
            letter_count++;
        if (letter_count == 0)
            continue;
        res[count] = malloc(sizeof(char) * (letter_count + 1));
        if (!res[count])
            return NULL;
        res[count][letter_count] = '\0';
        for (int y = i - letter_count; y < i; y++)
            res[count][y - i + letter_count] = str[y];
        count++;
    }
    return res;
}

static int not_in(char c, char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
        if (c == str[i])
            return 0;
    return 1;
}

int only_seperators(char *str, char *delim)
{
    for (int i = 0; str[i] != '\0'; i++)
        if (not_in(str[i], delim))
            return 0;
    return 1;
}

char **simple_split_str(char *str, char *delim)
{
    char **res = NULL;
    int words = 0;

    if (!str || !delim || only_seperators(str, delim))
        return NULL;
    words = count_words(str, delim);
    res = malloc(sizeof(char *) * (words + 1));
    if (!res)
        return NULL;
    res[words] = NULL;
    return words_to_array(res, str, delim);
}
