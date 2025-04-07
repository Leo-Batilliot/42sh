/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-minishell1-gabin.wilson
** File description:
** my_envcpy
*/

#include "my.h"

char **my_env_cpy(char **env)
{
    char **env_cpy = NULL;
    int count = 0;
    int i = 0;

    for (; env[count] != NULL; count++);
    env_cpy = malloc(sizeof(char *) * (count + 1));
    if (!env_cpy)
        return NULL;
    for (; env[i] != NULL; i++) {
        env_cpy[i] = malloc(sizeof(char) * my_strlen(env[i]) + 1);
        if (!env_cpy[i])
            return NULL;
        my_strcpy(env_cpy[i], env[i]);
    }
    env_cpy[i] = NULL;
    return env_cpy;
}
