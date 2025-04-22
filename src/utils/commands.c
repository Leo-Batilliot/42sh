/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-minishell1-gabin.wilson
** File description:
** my_gest_commands
*/

#include "my.h"

static int access_with_path(char *input, char **res, char **array, int i)
{
    *res = malloc(sizeof(char) * my_strlen(array[i]) + my_strlen(input) + 2);
    if (!(*res))
        return 0;
    my_strcpy((*res), array[i]);
    my_strcat((*res), "/");
    my_strcat((*res), input);
    if (!access((*res), X_OK)) {
        free_array((void **)array);
        return 1;
    }
    return 0;
}

static int access_with_pwd(char *pwd, char *input, char **res)
{
    *res = malloc(sizeof(char) * (my_strlen(input) + my_strlen(pwd) + 2));
    if (!*res)
        return 0;
    my_strcpy(*res, pwd);
    my_strcat(*res, "/");
    my_strcat(*res, input);
    if (!access(*res, X_OK))
        return 1;
    return 0;
}

static char *try_to_access(char *input, char *pwd, char *path)
{
    char *res = NULL;
    char **array = split_str(path, ":");

    if (!array)
        return NULL;
    for (int i = 0; array[i]; i++) {
        if (access_with_path(input, &res, array, i))
            return res;
        my_free(res);
        res = NULL;
    }
    free_array((void **)array);
    if (!pwd || pwd[0] == '\0')
        return NULL;
    if (access_with_pwd(pwd, input, &res))
        return res;
    my_free(res);
    return NULL;
}

static char *get_path(char *input, char *path, char *pwd)
{
    if (!path || path[0] == '\0')
        return NULL;
    if (input[0] == '/' || (input[0] == '.' && input[1] == '/'))
        return my_strdup(input);
    return try_to_access(input, pwd, path);
}

static int get_command_path(char **array, linked_list_t *head, shell_t *shell)
{
    if (!array[0])
        return 1;
    if (handle_color_command(array, shell))
        return -1;
    if (!is_builtin(array)) {
        shell->path = get_path(
            array[0], get_env_value("PATH", head), get_env_value("PWD", head));
        if (!shell->path) {
            mini_printf(2, "%s: Command not found.\n", array[0]);
            shell->last_exit = 1;
            my_free(shell->path);
            shell->path = NULL;
            return 1;
        }
    }
    return 0;
}

int execute_command_list(shell_t *shell, linked_list_t *head)
{
    for (args_t *tmp = shell->list->head; tmp; tmp = tmp->next) {
        if (get_command_path(tmp->args, head, shell))
            continue;
        free_array((void **)shell->env_cpy);
        shell->env_cpy = linked_list_to_array(head);
        if (!shell->env_cpy)
            return 0;
        execute_cmd(shell, tmp, &head);
        free_array((void **)shell->env_cpy);
        shell->env_cpy = NULL;
        free_array((void **)tmp->args);
        tmp->args = NULL;
    }
    if (shell->list)
        free_args_list(shell->list, 1);
    shell->list = NULL;
    return 0;
}
