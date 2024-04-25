//
// Created by plouvel on 24/04/24.
//

#include "ft_ls.h"
#include "libft.h"

int
sort_by_file_name(const void *a, const void *b) {
    const t_file *file_a = a;
    const t_file *file_b = b;

    return ft_strcmp_ignore_case(file_a->name, file_b->name) > 0;
}

int
sort_by_time(const void *a, const void *b) {
    const t_file *file_a = a;
    const t_file *file_b = b;

    return file_a->stat.st_mtime < file_b->stat.st_mtime;
}
