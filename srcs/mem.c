//
// Created by plouvel on 24/04/24.
//

#include <stdlib.h>

#include "ft_ls.h"

void
free_file_list(void *content) {
    t_file *file = content;

    free((void *)file->name);
    free(file);
}
