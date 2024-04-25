//
// Created by plouvel on 23/04/24.
//

#ifndef FT_LS_H
#define FT_LS_H

#include <limits.h>
#include <stdbool.h>
#include <sys/stat.h>

#define DEFAULT_PATH "."

typedef struct s_options {
    bool recursive : 1;
    bool reverse : 1;
    bool sort_by_time : 1;
    bool long_listing_format : 1;
    bool all : 1;
    bool help : 1;
} t_options;

typedef struct s_ft_ls {
    t_options   options;
    const char *path;
} t_ft_ls;

typedef struct s_file {
    char          name[NAME_MAX];
    unsigned char type;
    struct stat   stat;
} t_file;

#endif  // FT_LS_H
