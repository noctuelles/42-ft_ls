#include <stdio.h>

#include "ft_args_parser.h"
#include "ft_ls.h"
#include "ft_printf.h"
#include "parsing/opts.h"
#include "walk.h"
#include "wrapper.h"

static t_args_parser_option_entry g_parser_option_entries[] = {
    {
        .short_key                     = "l",
        .long_key                      = NULL,
        .argument                      = false,
        .long_key_argument_description = NULL,
        .description                   = "use a long listing format",
        .parse_fn                      = parse_long_listing,
    },
    {
        .short_key                     = "a",
        .long_key                      = "all",
        .argument                      = false,
        .long_key_argument_description = NULL,
        .description = "do not ignore entries starting with .",
        .parse_fn    = parse_all,
    },
    {
        .short_key                     = "t",
        .long_key                      = "time",
        .argument                      = false,
        .long_key_argument_description = NULL,
        .description = "sort by modification time, newest first",
        .parse_fn    = parse_time,
    },
    {
        .short_key                     = "r",
        .long_key                      = "reverse",
        .argument                      = false,
        .long_key_argument_description = NULL,
        .description                   = "reverse order while sorting",
        .parse_fn                      = parse_reverse,
    },
    {
        .short_key                     = "R",
        .long_key                      = "recursive",
        .argument                      = false,
        .long_key_argument_description = NULL,
        .description                   = "list subdirectories recursively",
        .parse_fn                      = parse_recursive,
    },

    {
        .short_key                     = "h",
        .long_key                      = "help",
        .argument                      = false,
        .long_key_argument_description = NULL,
        .description                   = "show this help",
        .parse_fn                      = parse_help,
    }

};

int
main(int argc, char** argv) {
    t_ft_ls ft_ls = {0};

    t_args_parser_config config = {
        .argc               = argc,
        .argv               = argv,
        .parser_entries     = g_parser_option_entries,
        .parser_entries_len = sizeof(g_parser_option_entries) /
                              sizeof(g_parser_option_entries[0]),
        .input             = &ft_ls,
        .parse_argument_fn = parse_argument,
    };

    if (ft_args_parser(&config) != 0) {
        return (1);
    }
    if (ft_ls.options.help) {
        ft_printf("usage: %s [options] [file ...]\n", argv[0]);
        ft_args_parser_print_docs(&config);
        return (0);
    }
    if (ft_ls.path == NULL) {
        ft_ls.path = DEFAULT_PATH;
    }
    if (file_walk(ft_ls.path, &ft_ls.options) == -1) {
        return (1);
    }

    return (0);
}
