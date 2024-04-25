//
// Created by plouvel on 23/04/24.
//

#include "ft_args_parser.h"
#include "ft_ls.h"

int
parse_argument(char *argument, t_args_parser_state *state, void *input) {
    (void)state;

    t_ft_ls *ls = input;
    ls->path    = argument;

    return 0;
}

int
parse_recursive(char *argument, t_args_parser_state *state, void *input) {
    (void)argument;
    (void)state;

    t_ft_ls *ls           = input;
    ls->options.recursive = true;

    return 0;
}

int
parse_reverse(char *argument, t_args_parser_state *state, void *input) {
    (void)argument;
    (void)state;

    t_ft_ls *ls         = input;
    ls->options.reverse = true;

    return 0;
}

int
parse_all(char *argument, t_args_parser_state *state, void *input) {
    (void)argument;
    (void)state;

    t_ft_ls *ls     = input;
    ls->options.all = true;

    return 0;
}

int
parse_long_listing(char *argument, t_args_parser_state *state, void *input) {
    (void)argument;
    (void)state;

    t_ft_ls *ls                     = input;
    ls->options.long_listing_format = true;

    return 0;
}

int
parse_time(char *argument, t_args_parser_state *state, void *input) {
    (void)argument;
    (void)state;

    t_ft_ls *ls              = input;
    ls->options.sort_by_time = true;

    return 0;
}

int
parse_help(char *argument, t_args_parser_state *state, void *input) {
    (void)argument;
    (void)state;

    t_ft_ls *ls      = input;
    ls->options.help = true;

    return 0;
}
