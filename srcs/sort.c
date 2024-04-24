//
// Created by plouvel on 24/04/24.
//

#include <stdbool.h>

#include "ft_ls.h"

int
sort_by_file_name(void *a, void *b) {
    const t_file *file_a = a;
    const t_file *file_b = b;

    return ft_strcmp(file_a->file_name, file_b->file_name) > 0;
}

int
sort_by_time(void *a, void *b) {
    const t_file *file_a = a;
    const t_file *file_b = b;

    (void)file_a;
    (void)file_b;
    return 0;
}
