/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-minishell2-mathis.korejezak
** File description:
** check_str.c
*/

int check_str(char *str)
{
    for (int i = 0; str[i]; i++) {
        if (str[i] != ' ' && str[i] != '\t')
            return 1;
    }
    return 0;
}
