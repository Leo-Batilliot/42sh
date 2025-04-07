/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-minishell1-gabin.wilson
** File description:
** my_print_prompt
*/

#include "my.h"

linked_list_t *print_prompt(char **env_cpy)
{
    linked_list_t *head = NULL;

    head = my_parse_env(env_cpy);
    if (!head)
        return NULL;
    return head;
}
