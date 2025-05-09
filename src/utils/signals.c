/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** signals
*/

#include <signal.h>

// name :   handle_signals
// args :   N.A
// use :    handle signals effects
void handle_signals(void)
{
    signal(SIGINT, SIG_IGN);
    signal(SIGTSTP, SIG_IGN);
}
