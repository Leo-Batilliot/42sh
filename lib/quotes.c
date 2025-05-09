/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** quotes
*/

#include "shell.h"
#include <stdlib.h>

int is_quote(char c)
{
    return (c == '"' || c == '\'');
}

void cond_in_quote(int *in_quotes, char *current_quote, const char *str, int i)
{
    if (*in_quotes == 0) {
        *in_quotes = 1;
        *current_quote = str[i];
    } else if (str[i] == *current_quote) {
        *in_quotes = 0;
    }
}

int is_in_quotes(const char *str, int pos)
{
    int i = 0;
    int in_quotes = 0;
    char current_quote = '\0';

    while (i < pos) {
        if (is_quote(str[i]) && (i == 0 || str[i - 1] != '\\'))
            cond_in_quote(&in_quotes, &current_quote, str, i);
        i++;
    }
    return in_quotes;
}

static int handle_quoted_content(const char *string,
    parser_t *parser, char **array)
{
    char quote_type = string[parser->i];

    parser->i++;
    for (; string[parser->i]; parser->i++) {
        if (string[parser->i] == quote_type &&
            (parser->i == 0 || string[parser->i - 1] != '\\')) {
            parser->i++;
            break;
        }
        array[parser->y][parser->x] = string[parser->i];
        parser->x++;
    }
    parser->i--;
    return 0;
}

int get_quoted_length(const char *string, int start_pos)
{
    int length = 0;
    char quote_char = string[start_pos];

    length++;
    while (string[start_pos + length] != '\0') {
        if (string[start_pos + length] == quote_char &&
            string[start_pos + length - 1] != '\\') {
            length++;
            return length;
        }
        length++;
    }
    return -1;
}

int handle_quote_allocation(const char *string, parser_t *parser,
    char **array)
{
    int total_len = get_quoted_length(string, parser->i);
    int content_len = (total_len == -1) ? -1 : total_len - 2;

    if (total_len == -1)
        return -1;
    if (content_len < 0)
        content_len = 0;
    array[parser->y] = malloc(sizeof(char) * (content_len + 1));
    if (!array[parser->y])
        return -1;
    return handle_quoted_content(string, parser, array);
}


int handle_quote(const char *string, char *operator,
    char ***array, parser_t *parser)
{
    if (parser->x > 0 && finish_word(array, parser) == -1)
        return -1;
    if (fill_array_str(string, operator, (*array), parser) == -1)
        return -1;
    if (parser->x > 0 && finish_word(array, parser) == -1)
        return -1;
    return 0;
}
