/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-minishell1-leo.batilliot
** File description:
** my_array_len
*/

// name :   array_len
// args :   an array (cast in const void ** if needed)
// use :    counts the number of cells in an array before NULL
int array_len(const void **array)
{
    int res = 0;

    if (!array)
        return res;
    for (; array[res]; res++);
    return res;
}
