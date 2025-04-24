/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** str_is_digits
*/

// name :   str_is_digits
// args :   string
// use :    S.E
int str_is_digits(const char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
        if (str[i] > '9' || str[i] < '0')
            return 0;
    return 1;
}
