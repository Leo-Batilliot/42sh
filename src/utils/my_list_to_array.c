/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-minishell1-gabin.wilson
** File description:
** my_list_to_array
*/

#include "shell.h"
#include <stddef.h>
#include <stdlib.h>

// name :   list_len
// args :   list
// use :    return the lenght of a list
int list_len(list_t *head)
{
    int count = 0;

    for (list_t *tmp = head; tmp; tmp = tmp->next)
        count++;
    return count;
}

// name :   fill_array
// args :   env list, array
// use :    fill an array using the env list
static int fill_array(list_t *head, char **array)
{
    int len = 0;
    int i = 0;

    for (list_t *cur = head; cur; cur = cur->next) {
        len = my_strlen(cur->key) + my_strlen(cur->value) + 2;
        array[i] = malloc(sizeof(char) * len);
        if (!array[i])
            return -1;
        my_strcpy(array[i], cur->key);
        my_strcat(array[i], "=");
        if (cur->value)
            my_strcat(array[i], cur->value);
        i++;
    }
    array[i] = NULL;
    return 0;
}

// name :   list_to_array
// args :   env list
// use :    create an array using the env list
char **list_to_array(list_t *head)
{
    char **array = NULL;
    int count = 0;

    count = list_len(head);
    array = malloc(sizeof(char *) * (count + 1));
    if (!array)
        return NULL;
    if (fill_array(head, array) == -1)
        return NULL;
    return array;
}
