/*
** EPITECH PROJECT, 2024
** B-MUL-100-LIL-1-1-myradar-gabin.wilson
** File description:
** Gestion des guillemets
*/

#include "shell.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int handle_quote_length(const char *string,
    parser_t *parser, int *word_len)
{
    int len_quote = get_quoted_length(string, parser->i);

    if (len_quote == -1) {
        fprintf(stderr, "Erreur: guillemet non");
        fprintf(stderr, " fermé à la position %d\n", parser->i);
        return -1;
    }
    *word_len = len_quote;
    return 0;
}

static void handle_keep_delim_length(const char *string,
    parser_t *parser, int *word_len)
{
    while (is_keep_delim(string[parser->i + *word_len]))
        (*word_len)++;
}

static void handle_standard_length(const char *string, parser_t *parser,
    int *word_len, char *operator)
{
    while (string[parser->i + *word_len] != '\0' &&
        !is_separator(string[parser->i + *word_len],
            operator, string, parser->i + *word_len) &&
        !is_delim(string[parser->i + *word_len]) &&
        !is_keep_delim(string[parser->i + *word_len]) &&
        !is_keep_alone(string[parser->i + *word_len])) {
        (*word_len)++;
    }
}

int update_length(const char *string, parser_t *parser,
    int *word_len, char *operator)
{
    if (is_quote(string[parser->i]))
        return handle_quote_length(string, parser, word_len);
    if (is_keep_alone(string[parser->i])) {
        *word_len = 1;
        return 0;
    }
    if (is_keep_delim(string[parser->i])) {
        handle_keep_delim_length(string, parser, word_len);
        return 0;
    }
    handle_standard_length(string, parser, word_len, operator);
    if (is_delim(string[parser->i]))
        *word_len = 1;
    return 0;
}

// name :   add_uop
// args :   string, parser_t *parser, array
// use :    add to operator
int add_uop(const char *string, parser_t *parser, char **array)
{
    if (is_keep_delim(string[parser->i]) && parser->add == 0) {
        parser->add = 1;
        parser->must = 1;
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
        parser->must = 1;
        parser->i--;
        return 0;
    }
    return 1;
}

static int allocate_array(const char *string, char *operator,
    char **array, parser_t *parser)
{
    int word_len = 0;

    if (is_quote(string[parser->i]))
        return handle_quote_allocation(string, parser, array);
    if (is_keep_alone(string[parser->i]))
        word_len = 1;
    else if (update_length(string, parser, &word_len, operator) == -1)
        return -1;
    array[parser->y] = malloc(sizeof(char) * (word_len + 1));
    if (!array[parser->y])
        return -1;
    return 0;
}

int fill_array_str(const char *string, char *operator,
    char **array, parser_t *parser)
{
    if (parser->x == 0)
        if (allocate_array(string, operator, array, parser) != 0)
            return (is_quote(string[parser->i])) ? 0 : -1;
    if (add_uop(string, parser, array) == 0)
        return 0;
    array[parser->y][parser->x] = string[parser->i];
    parser->x++;
    return 1;
}

int finish_word(char ***array, parser_t *parser)
{
    (*array)[parser->y][parser->x] = '\0';
    parser->y++;
    parser->x = 0;
    parser->must = 0;
    (*array) = realloc(*array, sizeof(char *) * (parser->y + 2));
    if (!(*array))
        return -1;
    return 0;
}

// name :   handle_keep_alone
// args :   string, array, parser_t *parser
// use :    handle word to keep alone
int handle_keep_alone(const char *string,
    char ***array, parser_t *parser)
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

static int handle_default(const char *string, char *operator,
    char ***array, parser_t *parser)
{
    if (fill_array_str(string, operator, (*array), parser) == -1)
        return -1;
    return 0;
}

static int handle_finish_if_needed(const char *string, char ***array,
    parser_t *parser, char *operator)
{
    if (is_delim(string[parser->i]) || parser->must == 1 ||
        is_delim(string[parser->i + 1]) ||
        is_separator(string[parser->i], operator, string, parser->i) ||
        string[parser->i + 1] == '\0') {
        if (parser->x > 0 && finish_word(array, parser) == -1)
            return -1;
    }
    return 0;
}

static int process_char(const char *string, char *operator,
    char ***array, parser_t *parser)
{
    if (is_quote(string[parser->i]) &&
        (parser->i == 0 || string[parser->i - 1] != '\\'))
        return handle_quote(string, operator, array, parser);
    if (is_keep_alone(string[parser->i])) {
        if (parser->x > 0 && finish_word(array, parser) == -1)
            return -1;
        return handle_keep_alone(string, array, parser);
    }
    if (!is_separator(string[parser->i], operator, string, parser->i))
        if (handle_default(string, operator, array, parser) == -1)
            return -1;
    if (handle_finish_if_needed(string, array, parser, operator) == -1)
        return -1;
    return 0;
}

// name :   declare_parser
// args :   nothing
// use :    declare struct for parser
static parser_t *declare_parser(void)
{
    parser_t *parser = malloc(sizeof(parser_t));

    if (!parser)
        return NULL;
    parser->i = 0;
    parser->x = 0;
    parser->y = 0;
    parser->add = 0;
    parser->must = 0;
    return parser;
}

// name :   ret_array
// args :   parser, array
// use :    return aray or NULL if error
char **ret_array(parser_t *parser, char **array)
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
