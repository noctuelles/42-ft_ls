
#include "walk.h"

#include <stdio.h>
#include <stdlib.h>

#include "ft_ls.h"
#include "mem.h"
#include "sort.h"
#include "wrapper.h"

static int
populate_file(const struct dirent* entry, t_file* file) {
    file->file_type = entry->d_type;
    if ((file->file_name = ft_strdup(entry->d_name)) == NULL) {
        return (-1);
    }
    return (0);
}

static int
create_file(const struct dirent* entry, t_dlist** list) {
    t_file*  file = NULL;
    t_dlist* elem = NULL;
    if ((file = malloc(sizeof(file))) == NULL) {
        goto err;
    }
    if (populate_file(entry, file) == -1) {
        goto err_file;
    }
    if ((elem = ft_dlstnew(file)) == NULL) {
        goto err_elem;
    }
    ft_dlstadd_back(list, elem);
    return (0);
err_elem:
    free((void*)file->file_name);
err_file:
    free(file);
err:
    return (-1);
}

static void
sort_file_list(t_dlist** list, const t_options* options) {
    int (*sort_fn)(void*, void*) = NULL;

    if (options->sort_by_time) {
        sort_fn = sort_by_time;
    } else {
        sort_fn = sort_by_file_name;
    }

    ft_dlstsort(list, sort_fn);
}

static void
process_file_list(t_dlist* list, const t_options* options) {
    t_file* file = NULL;

    if (options->reverse) {
        list = ft_dlstlast(list);
    }
    while (list != NULL) {
        file = list->content;

        if (options->recursive) {
        }

        printf("%s\n", file->file_name);

        if (options->reverse) {
            list = list->prev;
        } else {
            list = list->next;
        }
    }
}

int
file_walk(const char* path, const t_options* options) {
    DIR*           dir       = NULL;
    struct dirent* dir_entry = NULL;
    t_dlist*       file_list = NULL;

    if ((dir = w_opendir(path)) == NULL) {
        return (-1);
    }
    while ((dir_entry = w_readdir(dir)) != NULL) {
        create_file(dir_entry, &file_list);
    }
    sort_file_list(&file_list, options);
    process_file_list(file_list, options);
    ft_dlstclear(&file_list, free_file_list);
    (void)closedir(dir);
    return (0);
}
