/*
** EPITECH PROJECT, 2024
** B-MUL-100-LIL-1-1-myradar-gabin.wilson
** File description:
** my_get_nbr
*/

// name : my_atoi
// args : string
// use : takes a string as argument and convert its content to an int
int my_atoi(const char *string)
{
    long res = 0;

    if (!string)
        return 0;
    for (int i = 0; string[i] != '\0'; i++) {
        if (string[i] < '0' || string[i] > '9')
            return 0;
        res = res * 10 + string[i] - '0';
        if (res > 2147483647)
            return 0;
    }
    return res;
}
