/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** expand_variables.c
*/

#include "shell.h"
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// name :   get_variable_value
// args :   shell (shell_t *), var_name (const char *)
// use :    search for the value of a local variable named var_name in shell
char *get_variable_value(shell_t *shell, const char *var_name)
{
    for (list_t *node = shell->local_vars; node; node = node->next) {
        if (my_strcmp(node->key, var_name) == 0)
            return node->value;
    }
    return NULL;
}

// name :   copy_value_to_buffer
// args :   value (char *), dest (char *), index (size_t *)
// use :    copy a value into the buffer at the given index
static void copy_value_to_buffer(char *value, char *dest, size_t *index)
{
    for (size_t i = 0; value && value[i]; i++) {
        dest[(*index)] = value[i];
        (*index)++;
    }
}

// name :   extract_var_name
// args :   line (char *), start (size_t), var_len (size_t *)
// use :    extract the name of the variable starting at index `start`
static char *extract_var_name(char *line, size_t start, size_t *var_len)
{
    size_t i = start;

    while (line[i] && (isalnum(line[i]) || line[i] == '_'))
        i++;
    *var_len = i - start;
    return strndup(&line[start], *var_len);
}

// name :   realloc_if_needed
// args :   buffer (char **), current (size_t), capacity (size_t *)
// use :    realloc the buffer if the current index nears capacity
static void realloc_if_needed(char **buffer, size_t current, size_t *capacity)
{
    if (current + 2 > *capacity) {
        *capacity += 32;
        *buffer = realloc(*buffer, *capacity);
    }
}

// name :   handle_variable_expansion
// args :   line, shell, ctx
// use :    handles $VAR expansion from line into buffer using context
static void handle_variable_expansion(char *line, shell_t *shell,
    expansion_ctx_t *ctx)
{
    size_t var_len = 0;
    char *var_name = extract_var_name(line, *(ctx->i) + 1, &var_len);
    char *var_value = get_variable_value(shell, var_name);

    *(ctx->i) += var_len + 1;
    if (var_value)
        copy_value_to_buffer(var_value, *(ctx->buffer), ctx->j);
    free(var_name);
}

// name :   expand_variables
// args :   line (char *), shell (shell_t *)
// use :    expand variables like $VAR in the input line
char *expand_variables(char *line, shell_t *shell)
{
    size_t buf_size = strlen(line) + 1;
    size_t i = 0;
    size_t j = 0;
    char *expanded = malloc(buf_size);
    expansion_ctx_t ctx = { &i, &j, &expanded };

    if (!expanded)
        return NULL;
    while (i < strlen(line)) {
        if (line[i] == '$')
            handle_variable_expansion(line, shell, &ctx);
        else {
            expanded[j] = line[i];
            j++;
            i++;
        }
        realloc_if_needed(&expanded, j, &buf_size);
    }
    expanded[j] = '\0';
    return expanded;
}
