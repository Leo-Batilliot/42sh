/*
** EPITECH PROJECT, 2024
** B-MUL-100-LIL-1-1-myradar-gabin.wilson
** File description:
** my_get_nbr
*/

#include "my.h"

int verif(int nb, char *string, int *i)
{
    while (string[*i] >= 48 && string[*i] <= 57) {
        nb = nb * 10 + (string[*i] - 48);
        (*i)++;
        if (string[*i] < 48 || string[*i] > 57) {
            return nb;
        }
    }
    return nb;
}

int my_getnbr(char *string)
{
    int nb = 0;
    int i = 0;

    if (string == NULL)
        return 0;
    for (; string[i] != '\0'; i++) {
        if (string[i] >= 48 && string[i] <= 57) {
            nb = verif(nb, string, &i);
            break;
        }
    }
    return nb;
}
