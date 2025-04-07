/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-minishell1-gabin.wilson
** File description:
** my_list_to_array
*/

#include "my.h"

int get_count(linked_list_t *head)
{
    linked_list_t *tmp = head;
    int count = 0;

    while (tmp != NULL) {
        count++;
        tmp = tmp->next;
    }
    return count;
}

int fill_tab(linked_list_t *cur, int *i, int count, char **array)
{
    int len_value = 0;

    while (cur != NULL) {
        if (cur->value == NULL)
            len_value = 0;
        else
            len_value = my_strlen(cur->value);
        count = my_strlen(cur->key) + len_value + 2;
        array[(*i)] = malloc(sizeof(char) * count);
        if (!array[(*i)])
            return -1;
        my_strcpy(array[(*i)], cur->key);
        my_strcat(array[(*i)], "=");
        if (cur->value != NULL)
            my_strcat(array[(*i)], cur->value);
        cur = cur->next;
        (*i)++;
    }
    return 0;
}

char **linked_list_to_array(linked_list_t *head)
{
    char **array = NULL;
    int i = 0;
    int count = 0;
    linked_list_t *cur = head;

    count = get_count(head);
    array = malloc(sizeof(char *) * (count + 1));
    if (!array)
        return NULL;
    if (fill_tab(cur, &i, count, array) == -1)
        return NULL;
    array[i] = NULL;
    return array;
}
