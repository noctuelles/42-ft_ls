#include <dirent.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>

#include "ft_args_parser.h"

static const t_args_parser_option_entry parser_option_entries[] = {
    {
        .short_key                     = "l",
        .long_key                      = NULL,
        .argument                      = false,
        .long_key_argument_description = NULL,
        .description                   = "use a long listing format",
        .parse_fn                      = NULL,
    },
    {
        .short_key                     = "a",
        .long_key                      = "all",
        .argument                      = false,
        .long_key_argument_description = NULL,
        .description                   = "do not ignore entries starting with .",
        .parse_fn                      = NULL,
    },
    {
        .short_key                     = "t",
        .long_key                      = "time",
        .argument                      = false,
        .long_key_argument_description = NULL,
        .description                   = "sort by modification time, newest first",
        .parse_fn                      = NULL,
    }

};

void
read(const char* path) {
    DIR*           dir       = NULL;
    struct dirent* dir_entry = NULL;

    errno = 0;
    dir   = opendir(path);
    if (dir == NULL) {
        return;
    }
    while ((dir_entry = readdir(dir)) != NULL) {
    }
    (void)closedir(dir);
}

int
main() {
    return (0);
}
