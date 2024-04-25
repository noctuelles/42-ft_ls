//
// Created by plouvel on 23/04/24.
//

#ifndef OPTS_H
#define OPTS_H

#include "ft_args_parser.h"

int parse_argument(char *argument, t_args_parser_state *state, void *input);
int parse_recursive(char *argument, t_args_parser_state *state, void *input);
int parse_reverse(char *argument, t_args_parser_state *state, void *input);
int parse_all(char *argument, t_args_parser_state *state, void *input);
int parse_long_listing(char *argument, t_args_parser_state *state, void *input);
int parse_time(char *argument, t_args_parser_state *state, void *input);
int parse_help(char *argument, t_args_parser_state *state, void *input);

#endif  // OPTS_H
