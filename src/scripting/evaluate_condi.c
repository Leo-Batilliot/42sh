/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** evaluate_condi.c
*/

#include "shell.h"
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// name :   trim_line
// args :   line
// use :    removes leading and trailing whitespaces from a string
void trim_line(char *line)
{
    char *start = line;
    char *end = NULL;

    while (*start && isspace((unsigned char)*start))
        start++;
    end = start + strlen(start) - 1;
    while (end > start && isspace((unsigned char)*end))
        end--;
    *(end + 1) = '\0';
    memmove(line, start, end - start + 2);
}

// name :   extract_condition_sides
// args :   cond, left, right
// use :  extracts left and right sides of condition from the duplicated string
static int extract_condition_sides(char *cond, char **left, char **right)
{
    *left = strtok(cond, " =");
    *right = strtok(NULL, " =");
    if (!*left || !*right)
        return 0;
    trim_line(*left);
    trim_line(*right);
    return 1;
}

// name :   resolve_condition_values
// args :   shell, left, right
// use :    resolves variable values if they exist
static void resolve_condition_values(shell_t *shell, char **left, char **right)
{
    char *val_left = get_variable_value(shell, *left);
    char *val_right = get_variable_value(shell, *right);

    if (val_left)
        *left = val_left;
    if (val_right)
        *right = val_right;
}

// name :   evaluate_condition
// args :   condition, shell
// use :    evaluates a condition (VAR = VALUE) based on shell variables
int evaluate_condition(const char *condition, shell_t *shell)
{
    char *cond = NULL;
    char *left = NULL;
    char *right = NULL;
    int result = 0;

    cond = strdup(condition);
    if (!cond)
        return 0;
    if (!extract_condition_sides(cond, &left, &right)) {
        free(cond);
        return 0;
    }
    resolve_condition_values(shell, &left, &right);
    result = (my_strcmp(left, right) == 0);
    free(cond);
    return result;
}
