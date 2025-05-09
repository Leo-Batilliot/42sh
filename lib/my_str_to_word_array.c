/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-minishell2-mathis.korejezak
** File description:
** my_str_to_word_array.c
*/

#include "shell.h"
#include <stdlib.h>

// name :   separator
// args :   str (char const *), sep (char const *)
// use :    checks if the current character is a separator or newline
int separator(char const *str, char const *sep)
{
    for (int i = 0; sep[i] != '\0'; i++) {
        if (*str == sep[i] || *str == '\n')
            return 1;
    }
    return 0;
}

// name :   word_len
// args :   str (char const *), sep (char const *)
// use :    calculates the length of the word before the next separator
int word_len(char const *str, char const *sep)
{
    int i = 0;

    while (str[i] != '\0' && !separator(&str[i], sep)) {
        i++;
    }
    return i;
}

// name :   count_words
// args :   str (char const *), sep (char const *)
// use :    counts how many words are in the string based on separators
int count_words(char const *str, char const *sep)
{
    int i = 0;
    int word_count = 0;

    while (str[i] != '\0') {
        if (!separator(&str[i], sep) &&
            (separator(&str[i + 1], sep) || str[i + 1] == '\0')) {
            word_count++;
        }
        i++;
    }
    return word_count;
}

// name :   fill_word
// args :   array (char *), str (char const *), i (int *), sep (char const *)
// use :    copies one word from str into array, updates i to the next position
void fill_word(char *array, char const *str, int *i, char const *sep)
{
    int j = 0;

    while (str[*i] != '\0' && !separator(&str[*i], sep)) {
        array[j] = str[*i];
        j++;
        (*i)++;
    }
    array[j] = '\0';
    while (str[*i] != '\0' && separator(&str[*i], sep)) {
        (*i)++;
    }
}

// name :   my_str_to_word_array
// args :   str (char const *), sep (char const *)
// use :    splits a string into an array of words using given separators
char **my_str_to_word_array(char const *str, char const *sep)
{
    int words_count = count_words(str, sep);
    char **array = malloc(sizeof(char *) * (words_count + 1));
    int index = 0;
    int len = 0;

    if (!array)
        return NULL;
    while (str[index] != '\0' && separator(&str[index], sep))
        index++;
    for (int i = 0; i < words_count; i++) {
        len = word_len(&str[index], sep);
        array[i] = malloc(sizeof(char) * (len + 1));
        if (!array[i]) {
            free_array((void **)array);
            return NULL;
        }
        fill_word(array[i], str, &index, sep);
    }
    array[words_count] = NULL;
    return array;
}
