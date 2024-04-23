//
// Created by plouvel on 23/04/24.
//

#ifndef FT_LS_H
#define FT_LS_H

#include <stdbool.h>

typedef struct s_ft_ls {
    struct {
        bool recursive : 1;
        bool sort_reverse : 1;
        bool sort_by_time : 1;
        bool long_listing_format : 1;
        bool all : 1;
    } options;
    const char *path;
} t_ft_ls;

typedef struct s_file {
    const char        *name;
    const struct stat *statbuf;
} t_file;

#endif  // FT_LS_H
