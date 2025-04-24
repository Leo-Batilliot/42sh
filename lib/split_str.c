/*
** EPITECH PROJECT, 2024
** B-MUL-100-LIL-1-1-myradar-gabin.wilson
** File description:
** my_str_to_word_array
*/

#include "shell.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static const char *delim = ";";

static const char *array[] = {"<", ">", "|", "&", NULL};

int is_separator(const char c, char *ope)
{
    for (int i = 0; ope[i] != '\0'; i++)
        if (c == ope[i])
            return 1;
    return 0;
}

int is_delim(const char c)
{
    for (int i = 0; delim[i] != '\0'; i++)
        if (c == delim[i])
            return 1;
    return 0;
}

static int is_keep_delim(char c)
{
    for (int i = 0; array[i]; i++) {
        if (array[i][0] == c)
            return 1;
    }
    return 0;
}

static int update_length(const char *string, int index[5],
    int *word_len, char *operator)
{
    if (is_keep_delim(string[index[0] + (*word_len)])) {
        while (is_keep_delim(string[index[0] + (*word_len)]))
            (*word_len)++;
        return 0;
    }
    while (!is_separator(string[index[0] + (*word_len)], operator)
        && !is_delim(string[index[0] + (*word_len)])
        && !is_keep_delim(string[index[0] + (*word_len)])
        && string[index[0] + (*word_len)] != '\0')
            (*word_len)++;
    if (is_delim(string[index[0]]) && is_delim(string[index[0] + 1])) {
        while (is_delim(string[index[0] + 1]) && string[index[0]] != '\0')
            index[0]++;
    }
    if (is_delim(string[index[0]]))
        (*word_len) = 1;
    return 0;
}

static int add_uop(const char *string, int index[5], char **array)
{
    if (is_keep_delim(string[index[0]]) && index[3] == 0) {
        index[3] = 1;
        index[4] = 1;
        index[0]--;
        return 0;
    }
    if (index[3] == 1) {
        while (is_keep_delim(string[index[0]])) {
            array[index[2]][index[1]] = string[index[0]];
            index[1]++;
            index[0]++;
        }
        index[3] = 0;
        index[4] = 1;
        index[0]--;
        return 0;
    }
    return 1;
}

int fill_array(const char *string, char *operator, char **array, int index[5])
{
    int word_len = 0;

    if (index[1] == 0) {
        word_len = 0;
        update_length(string, index, &word_len, operator);
        array[index[2]] = malloc(sizeof(char) * (word_len + 1));
        if (!array[index[2]])
            return -1;
    }
    if (add_uop(string, index, array) == 0)
        return 0;
    array[index[2]][index[1]] = string[index[0]];
    index[1]++;
    return 1;
}

int process_char(const char *string, char *operator,
    char **array, int index[5])
{
    if (!is_separator(string[index[0]], operator) || string[index[0]] == '<') {
        if (fill_array(string, operator, array, index) == -1)
            return -1;
    }
    if (is_delim(string[index[0]]) ||
        index[4] == 1 ||
        is_delim(string[index[0] + 1]) ||
        is_separator(string[index[0]], operator) ||
        string[index[0] + 1] == '\0') {
        if (index[1] > 0) {
            array[index[2]][index[1]] = '\0';
            index[2]++;
            index[1] = 0;
            index[4] = 0;
        }
    }
    return 0;
}

char **split_str(const char *string, char *operator)
{
    int count = count_word(string, operator);
    char **array = NULL;
    int index[5] = {0, 0, 0, 0, 0};

    if (count == 0)
        return NULL;
    array = malloc(sizeof(char *) * (count + 1));
    if (!array || !string)
        return NULL;
    for (; string[index[0]] != '\0'; index[0]++) {
        if (process_char(string, operator, array, index) == -1)
            return NULL;
    }
    array[index[2]] = NULL;
    return array;
}
