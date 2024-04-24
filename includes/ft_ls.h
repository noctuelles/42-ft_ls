//
// Created by plouvel on 23/04/24.
//

#ifndef FT_LS_H
#define FT_LS_H

#include <stdbool.h>
#include <stdint.h>

#include "libft.h"

typedef struct s_options {
    bool recursive : 1;
    bool reverse : 1;
    bool sort_by_time : 1;
    bool long_listing_format : 1;
    bool all : 1;
} t_options;

typedef struct s_ft_ls {
    t_options   options;
    const char *path;
} t_ft_ls;

typedef struct s_file {
    const char   *file_name;
    unsigned char file_type;
    uint16_t      file_mode : 10;
} t_file;

#endif  // FT_LS_H
