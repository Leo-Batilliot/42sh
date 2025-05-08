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

// name :   update_length
// args :   string, parser_t *parser, world_len, operator
// use :    update lenght of new_word
static int update_length(const char *string, parser_t *parser,
    int *word_len, char *operator)
{
    if (is_keep_alone(string[parser->i])) {
        (*word_len) = 1;
        return 0;
    }
    if (is_keep_delim(string[parser->i])) {
        while (is_keep_delim(string[parser->i + (*word_len)]))
            (*word_len)++;
        return 0;
    }
    while (string[parser->i + (*word_len)] != '\0' &&
        !is_separator(string[parser->i + (*word_len)], operator) &&
        !is_delim(string[parser->i + (*word_len)]) &&
        !is_keep_delim(string[parser->i + (*word_len)]) &&
        !is_keep_alone(string[parser->i + (*word_len)])) {
        (*word_len)++;
    }
    if (is_delim(string[parser->i]))
        (*word_len) = 1;
    return 0;
}

// name :   add_uop
// args :   string, parser_t *parser, array
// use :    add to operator
static int add_uop(const char *string, parser_t *parser, char **array)
{
    if (is_keep_delim(string[parser->i]) && parser->add == 0) {
        parser->add = 1;
        parser->force = 1;
        parser->i--;
        return 0;
    }
    if (parser->add == 1) {
        while (is_keep_delim(string[parser->i])) {
            array[parser->y][parser->x] = string[parser->i];
            parser->x++;
            parser->i++;
        }
        parser->add = 0;
        parser->force = 1;
        parser->i--;
        return 0;
    }
    return 1;
}

// name :   fill_array
// args :   string, operator, array, parser_t *parser
// use :    fill new array split
static int fill_array(const char *string, char *operator,
    char **array, parser_t *parser)
{
    int word_len = 0;

    if (parser->x == 0) {
        word_len = 0;
        if (is_keep_alone(string[parser->i]))
            word_len = 1;
        else
            update_length(string, parser, &word_len, operator);
        array[parser->y] = malloc(sizeof(char) * (word_len + 1));
        if (!array[parser->y])
            return -1;
    }
    if (add_uop(string, parser, array) == 0)
        return 0;
    array[parser->y][parser->x] = string[parser->i];
    parser->x++;
    return 1;
}

// name :   handle_keep_alone
// args :   string, array, parser_t *parser
// use :    handle word to keep alone
int handle_keep_alone(const char *string, char ***array, parser_t *parser)
{
    (*array)[parser->y] = malloc(sizeof(char) * 2);
    if (!(*array)[parser->y])
        return -1;
    (*array)[parser->y][0] = string[parser->i];
    (*array)[parser->y][1] = '\0';
    parser->y++;
    (*array) = realloc(*array, sizeof(char *) * (parser->y + 2));
    if (!(*array))
        return -1;
    return 0;
}

// name :   finish_word
// args :   array, parser_t *parser
// use :    end of word
static int finish_word(char ***array, parser_t *parser)
{
    (*array)[parser->y][parser->x] = '\0';
    parser->y++;
    parser->x = 0;
    parser->force = 0;
    (*array) = realloc(*array, sizeof(char *) * (parser->y + 2));
    if (!(*array))
        return -1;
    return 0;
}

// name :   process_char
// args :   string, operator, array, parser_t *parser
// use :    process char
static int process_char(const char *string, char *operator,
    char ***array, parser_t *parser)
{
    if (is_keep_alone(string[parser->i])) {
        if (parser->x > 0 && finish_word(array, parser) == -1)
                return -1;
        return handle_keep_alone(string, array, parser);
    }
    if (!is_separator(string[parser->i], operator)) {
        if (fill_array(string, operator, (*array), parser) == -1)
            return -1;
    }
    if (is_delim(string[parser->i]) ||
        parser->force == 1 ||
        is_delim(string[parser->i + 1]) ||
        is_separator(string[parser->i], operator) ||
        string[parser->i + 1] == '\0') {
        if (parser->x > 0 && finish_word(array, parser) == -1)
            return -1;
    }
    return 0;
}

// name :   declare_parser
// args :   nothing
// use :    declare struct for parser
parser_t *declare_parser(void)
{
    parser_t *parser = malloc(sizeof(parser_t));

    if (!parser)
        return NULL;
    parser->i = 0;
    parser->x = 0;
    parser->y = 0;
    parser->add = 0;
    parser->force = 0;
    return parser;
}

static char **ret_array(parser_t *parser, char **array)
{
    if (parser->y == 0) {
        free(array);
        free(parser);
        return NULL;
    }
    array[parser->y] = NULL;
    free(parser);
    return array;
}

// name :   split_str
// args :   string, operator
// use :    S.E
char **split_str(const char *string, char *operator)
{
    char **array = NULL;
    parser_t *parser = declare_parser();

    if (!parser || !string)
        return NULL;
    array = malloc(sizeof(char *) * 2);
    if (!array) {
        free(parser);
        return NULL;
    }
    for (; string[parser->i] != '\0'; parser->i++) {
        if (process_char(string, operator, &array, parser) == -1) {
            free(parser);
            return NULL;
        }
    }
    return ret_array(parser, array);
}
