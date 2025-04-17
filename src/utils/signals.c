/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** signals.c
*/

#include "my.h"

void signal_handler(int signal)
{
    (void)signal;
    mini_printf("\n$> ");
}

void init_signals(void)
{
    signal(SIGINT, signal_handler);
}
