/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** completion_main
*/

#include "line_edition.h"
#include <unistd.h>

// name :   completion_loop
// args :   termios struct, completion struct
// use :    main loop for auto completion
int completion_loop(termios_t *termios, completion_t *completion)
{
    int res = 0;

    refresh_window_size(completion);
    res = auto_completion_input(termios, completion);
    delete_print(completion);
    update_command_line(termios, completion);
    if (res == 84)
        return 1;
    if (res == 1)
        return replace(termios, completion);
    display_completion_options(completion);
    return 0;
}

// name :   auto_completion
// args :   termios main struct
// use :    S.E
int auto_completion(termios_t *termios)
{
    completion_t *completion = init_completion(termios);

    if (!completion)
        return 0;
    for (int i = 1; i > 0; i = read(0, &(termios->input), 1)) {
        if (completion_loop(termios, completion))
            return free_completion(completion);
    }
    update_command_line(termios, completion);
    return free_completion(completion);
}
