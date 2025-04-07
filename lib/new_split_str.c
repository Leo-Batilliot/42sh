/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-minishell2-leo.batilliot
** File description:
** new_split_str
*/
#include "my.h"

int is_space(char c)
{
    return (c == ' ' || c == '\t' || c == '\n');
}

int only_spaces(const char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
        if (!is_space(str[i]) && str[i] != '"')
            return 0;
    return 1;
}

static int count_quoted_words(const char *str)
{
    int count = 0;
    int in_word = 0;
    int quotes = 0;
    int current = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        quotes ^= (str[i] == '"');
        current = (!is_space(str[i]) || quotes);
        if (current != in_word) {
            in_word = current;
            count += in_word;
        }
    }
    return count;
}

static int word_length(const char *str, int start)
{
    int length = 0;
    int quotes = 0;

    for (int i = start; str[i] != '\0'; i++) {
        if (str[i] == '"') {
            quotes = !quotes;
            continue;
        }
        if (is_space(str[i]) && !quotes)
            break;
        length++;
    }
    return length;
}

static char *extract_word(const char *str, int start, int length)
{
    char *word = malloc(sizeof(char) * (length + 1));
    int j = 0;
    int quotes = 0;

    if (!word)
        return NULL;
    for (int i = start; j < length; i++) {
        if (str[i] == '"') {
            quotes = !quotes;
            continue;
        }
        word[j] = str[i];
        j++;
    }
    word[length] = '\0';
    return word;
}

static void words_loop(const char *str, int *i, int *quotes, int *len)
{
    if (str[*i] == '"')
        *quotes = !*quotes;
    else if (!is_space(str[*i]) || *quotes)
        *(len) -= 1;
    *i += 1;
}

static char **words_to_quoted_array(char **res, const char *str, int words)
{
    int word_idx = 0;
    int i = 0;
    int quotes = 0;
    int len = 0;

    while (str[i] != '\0' && word_idx < words) {
        for (; is_space(str[i]) && !quotes; i++);
        if (str[i] == '\0')
            break;
        len = word_length(str, i);
        res[word_idx] = extract_word(str, i, len);
        if (!res[word_idx])
            return NULL;
        for (; len > 0 || (str[i] == '"'); words_loop(str, &i, &quotes, &len));
        word_idx++;
    }
    res[word_idx] = NULL;
    return res;
}

char **split_str_quotes(const char *str)
{
    char **res = NULL;
    int words = 0;

    if (!str || only_spaces(str))
        return NULL;
    words = count_quoted_words(str);
    if (words == 0)
        return NULL;
    res = malloc(sizeof(char *) * (words + 1));
    if (!res)
        return NULL;
    return words_to_quoted_array(res, str, words);
}
