/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** scripting.c
*/

#include "shell.h"
#include <unistd.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

// name :   is_script
// args :   path
// use :    returns 1 if the file is a 42sh script, 0 otherwise
int is_script(const char *path)
{
    FILE *file = fopen(path, "r");
    char line[256];

    if (!file)
        return 0;
    if (fgets(line, sizeof(line), file) == NULL) {
        fclose(file);
        return 0;
    }
    fclose(file);
    return my_strncmp(line, "#!", 2) == 0 && strstr(line, "42sh") != NULL;
}

// name :   execute_script_line
// args :   line, shell, node
// use :    interprets and executes a single line of the script
static void execute_script_line(char *line, shell_t *shell, node_t *node)
{
    char *expanded = NULL;
    char **args = NULL;

    trim_line(line);
    if (line[0] == '\0' || line[0] == '#')
        return;
    expanded = expand_variables(line, shell);
    args = my_str_to_word_array(expanded, " \t");
    if (!args || !args[0]) {
        free_array((void **)args);
        return free(expanded);
    }
    node->argv = args;
    if (is_builtin(args[0]))
        exec_builtin(args, shell);
    else
        mini_printf(2, "Commande inconnue : %s\n", expanded);
    free(expanded);
}

// name :   execute_if_lines
// args :   lines, shell, node
// use :    executes the commands in a valid if block
static void execute_if_lines(char **lines, shell_t *shell, node_t *node)
{
    for (int i = 1; lines[i]; i++) {
        if (my_strcmp(lines[i], "endif") == 0)
            break;
        execute_script_line(lines[i], shell, node);
    }
}

// name :   interpret_if_block
// args :   block_lines, shell, node
// use :    executes lines in an if/endif block if condition is true
static void interpret_if_block(char **block_lines, shell_t *shell,
    node_t *node)
{
    char *condition = extract_condition(block_lines[0]);
    char *resolved = NULL;

    if (!condition)
        return;
    resolved = expand_variables(condition, shell);
    if (evaluate_condition(resolved, shell))
        execute_if_lines(block_lines, shell, node);
    free(condition);
    free(resolved);
}

// name :   process_if_block
// args :   ctx, shell, node
// use :    executes a full if block and frees the used lines
static void process_if_block(script_ctx_t *ctx, shell_t *shell, node_t *node)
{
    int i = 0;

    ctx->if_block[ctx->block_index] = NULL;
    interpret_if_block(ctx->if_block, shell, node);
    while (i < ctx->block_index) {
        free(ctx->if_block[i]);
        i++;
    }
}

// name :   start_if_block
// args :   line, ctx
// use :    initializes a new if block with the opening line
static void start_if_block(char *line, script_ctx_t *ctx)
{
    ctx->if_block[ctx->block_index] = my_strdup(line);
    ctx->block_index++;
    ctx->if_mode = 1;
}

// name :   append_if_block
// args :   line, ctx, shell, node
// use :   appends a line to the current if block and evaluates it if completed
static void append_if_block(char *line, script_ctx_t *ctx,
    shell_t *shell, node_t *node)
{
    ctx->if_block[ctx->block_index] = my_strdup(line);
    ctx->block_index++;
    if (my_strcmp(line, "endif") == 0) {
        process_if_block(ctx, shell, node);
        ctx->block_index = 0;
        ctx->if_mode = 0;
    }
}

// name :   handle_line
// args :   line, ctx, shell, node
// use :    handles the execution of a script line, including if block logic
static void handle_line(char *line, script_ctx_t *ctx,
    shell_t *shell, node_t *node)
{
    if (!ctx->if_block)
        ctx->if_block = malloc(sizeof(char *) * 100);
    if (my_strncmp(line, "if ", 3) == 0)
        start_if_block(line, ctx);
    else if (ctx->if_mode)
        append_if_block(line, ctx, shell, node);
    else
        execute_script_line(line, shell, node);
}

// name :   execute_script
// args :   path, shell, node
// use :    runs a .42sh script by parsing and executing each line
int execute_script(const char *path, shell_t *shell, node_t *node)
{
    FILE *file = fopen(path, "r");
    char *line = NULL;
    size_t size = 0;
    script_ctx_t ctx = {0};

    if (!file) {
        mini_printf(2, "Erreur : impossible d’ouvrir %s\n", path);
        return 1;
    }
    while (getline(&line, &size, file) != -1) {
        trim_line(line);
        handle_line(line, &ctx, shell, node);
        free(line);
        line = NULL;
    }
    fclose(file);
    free(ctx.if_block);
    return 0;
}
