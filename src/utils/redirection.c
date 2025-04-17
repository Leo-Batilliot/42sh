/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-minishell2-gabin.wilson
** File description:
** handle_redirections
*/

#include "my.h"

static int end_heredoc(char *line, int i, args_t *tmp, int index)
{
    char *temp_line = my_strdup(line);

    if (!temp_line)
        return 0;
    temp_line[my_strlen(temp_line) - 1] = '\0';
    if (!my_strcmp(temp_line, tmp->redir[i].file)) {
        free(temp_line);
        return 1;
    }
    free(temp_line);
    write(index, line, my_strlen(line));
    write(STDOUT_FILENO, "? ", 2);
    return 0;
}

static int handle_fd(int fd, shell_t *shell, args_t *tmp, int std_fd)
{
    if (fd == -1) {
        fprintf(stderr, "%s: %s.\n",
            tmp->redir[tmp->redir->i].file, strerror(errno));
        shell->last_exit = 1;
        return 1;
    }
    if (dup2(fd, std_fd) == -1)
        return 1;
    close(fd);
    return 0;
}

static int heredoc(args_t *tmp, int i, shell_t *shell)
{
    int fd[2];
    size_t size = 0;
    char *line = NULL;

    if (pipe(fd) == -1)
        return 1;
    write(STDOUT_FILENO, "? ", 2);
    for (ssize_t read_size = getline(&line, &size, stdin); read_size != -1;
        read_size = getline(&line, &size, stdin))
        if (end_heredoc(line, i, tmp, fd[1]))
            break;
    free(line);
    close(fd[1]);
    if (handle_fd(fd[0], shell, tmp, STDIN_FILENO))
        return -1;
    return 0;
}

int redirection(args_t *tmp, shell_t *shell)
{
    int open_flags[3] = {O_RDONLY, O_WRONLY | O_CREAT | O_TRUNC,
        O_WRONLY | O_CREAT | O_APPEND};
    int fds[3] = {STDIN_FILENO, STDOUT_FILENO, STDOUT_FILENO};

    for (int i = 0; i < tmp->count_red; i++) {
        tmp->redir->i = 0;
        if (tmp->redir[i].status >= 1 && tmp->redir[i].status <= 3)
            return handle_fd(open(
                tmp->redir[i].file, open_flags[tmp->redir[i].status], 0644),
                shell, tmp, fds[tmp->redir[i].status]);
        if (tmp->redir[i].status == 4)
            return (heredoc(tmp, i, shell) == -1) ? 1 : 0;
    }
    return 0;
}
