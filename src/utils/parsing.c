/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-minishell2-gabin.wilson
** File description:
** parse
*/

#include "shell.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>


// name :   missing_name_message
// args :   shell
// use :    message for missing name
void *missing_name_message(shell_t *shell)
{
    mini_printf(2, "Missing name for redirect.\n");
    shell->last_exit = 1;
    shell->err = 1;
    return NULL;
}

// name :   missing_name_message
// args :   shell
// use :    message error for commands null
void *null_cmd(shell_t *shell)
{
    mini_printf(2, "Invalid null command.\n");
    shell->last_exit = 1;
    shell->err = 1;
    return NULL;
}

// name :   find_main_operator
// args :   tokens, start, end
// use :    find the last operator of line
static int find_main_operator(char **tokens, int start, int end)
{
    int paren_depth = 0;

    for (int i = end - 1; i >= start; i--) {
        if (strcmp(tokens[i], ")") == 0)
            paren_depth++;
        if (strcmp(tokens[i], "(") == 0)
            paren_depth--;
        if (paren_depth == 0 && is_operator(tokens[i]))
            return i;
    }
    return -1;
}

// name :   cpy_parts_args
// args :   tokens, start, end
// use :    copy a segment of args
static char **cpy_parts_args(char **tokens, int start, int end)
{
    int count = end - start;
    char **argv = NULL;

    if (count < 1)
        return NULL;
    argv = malloc(sizeof(char *) * (count + 1));
    if (!argv)
        return NULL;
    for (int i = 0; i < count; i++) {
        if (array_len((const void **)tokens) < start + i)
            return NULL;
        argv[i] = my_strdup(tokens[start + i]);
        if (!argv[i])
            return NULL;
    }
    argv[count] = NULL;
    return argv;
}

// name :   parsing_subshell
// args :   tokens, start, end, shell
// use :    parse the subshell for recursive function
static node_t *parsing_subshell(char **tokens, int start,
    int end, shell_t *shell)
{
    node_t *subshell_node = init_node();

    subshell_node->type = NODE_SUBSHELL;
    subshell_node->left = parse_tokens(tokens, start + 1, end - 1, shell);
    subshell_node->right = NULL;
    subshell_node->op = NULL;
    subshell_node->argv = NULL;
    return subshell_node;
}

// name :   free_arrays_and_node
// args :   2 arrays, a node, and the shell
// use :    S.E
static void *free_arrays_and_node(char **a, char **b, node_t *d, shell_t *shll)
{
    free_array((void **)a);
    free_array((void **)b);
    free_nodes(d);
    if (shll)
        shll->last_exit = 1;
    return NULL;
}

// name :   parsing_cmd
// args :   tokens, start, end, shell
// use :    parse commands for recursive functions
static node_t *parsing_cmd(char **tokens, int start, int end, shell_t *shell)
{
    node_t *cmd = init_node();
    char **new_array = NULL;
    char **args_array = NULL;

    if (!cmd)
        return free_arrays_and_node(NULL, NULL, NULL, shell);
    cmd->type = NODE_CMD;
    args_array = cpy_parts_args(tokens, start, end);
    new_array = replace_alias(shell, args_array);
    free_array((void **)args_array);
    if (!new_array)
        return free_arrays_and_node(NULL, NULL, cmd, shell);
    cmd->argv = globbings(new_array);
    if (!cmd->argv)
        return free_arrays_and_node(new_array, NULL, cmd, shell);
    free_arrays_and_node(new_array, NULL, NULL, NULL);
    return cmd;
}

// name :   bad_pipe
// args :   start, end, tokens
// use :    check if bad_pipe
static int bad_pipe(int start, int end, char **tokens)
{
    for (int i = start; i < end; i++) {
        if (strchr(tokens[i], '|')
            && strlen(tokens[i]) > 1
            && strcmp(tokens[i], "||"))
                return 1;
    }
    return 0;
}

// name :   parsing_op
// args :   stokens, start, end
// use :    use for parsing node with operator "|, ||, ;, &&"
node_t *parsing_op(char **tokens, int start, int end, shell_t *shell)
{
    int op_pos = find_main_operator(tokens, start, end);
    node_t *node = NULL;

    if (bad_pipe(start, end, tokens))
        return null_cmd(shell);
    if (op_pos != -1) {
        if (op_pos == start || op_pos == end - 1)
            return null_cmd(shell);
        node = init_node();
        if (!node)
            return NULL;
        node->type = NODE_OP;
        node->op = strdup(tokens[op_pos]);
        if (!node->op)
            return NULL;
        node->left = parse_tokens(tokens, start, op_pos, shell);
        node->right = parse_tokens(tokens, op_pos + 1, end, shell);
        return node;
    }
    return NULL;
}

// name :   parse_tokens
// args :   stokens, start, end, shell
// use :    main function for parsing
node_t *parse_tokens(char **tokens, int start, int end, shell_t *shell)
{
    node_t *op = NULL;

    shell->err = 0;
    if (strcmp(tokens[start], "(") == 0 && strcmp(tokens[end - 1], ")") == 0)
        return parsing_subshell(tokens, start, end, shell);
    op = parsing_op(tokens, start, end, shell);
    if (op || shell->err == 1)
        return op;
    op = parsing_redir(tokens, start, end, shell);
    if (op || shell->err == 1)
        return op;
    return parsing_cmd(tokens, start, end, shell);
}
