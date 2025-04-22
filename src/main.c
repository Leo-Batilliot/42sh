/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-minishell1-gabin.wilson
** File description:
** main
*/
#include "my.h"

static void reset_prompt(shell_t *shell)
{
    char *path = get_env_value("PWD", shell->env);

    if (isatty(0) == 1) {
        if (path)
            mini_printf(1, "%s%s> %s", shell->prompt_color, path,
                colors[8].code);
        else
            mini_printf(1, "%s$> %s", shell->prompt_color, colors[8].code);
    }
}

int main_loop(shell_t *shell)
{
    size_t size;

    while (1) {
        reset_prompt(shell);
        if (!shell->env)
            continue;
        if (getline(&shell->line, &size, stdin) == -1)
            return shell->last_exit;
        if (add_to_history(shell, shell->line))
            continue;
        if (!shell->line || shell->line[0] == '\n' || parse_args(shell))
            continue;
        execute_command_list(shell);
    }
    return 0;
}

int main(int ac, char **av, char **env)
{
    shell_t *shell = NULL;
    int res = 84;

    (void)av;
    if (ac != 1)
        return res;
    shell = init_shell(env);
    if (!shell)
        return res;
    shell->env = init_env(shell->env_cpy);
    if (!shell->env)
        free_and_exit(shell, res);
    load_file(shell);
    free_and_exit(shell, main_loop(shell));
    return 84;
}
