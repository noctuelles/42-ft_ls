
#include <stdio.h>
#include <stdlib.h>

#include "ft_ls.h"
#include "libft.h"
#include "mem.h"
#include "sort.h"
#include "utils.h"
#include "wrapper.h"

static int
populate_file(const struct dirent* entry, t_file* file, const t_options* options) {
    file->type = entry->d_type;
    if ((file->name = ft_strdup(entry->d_name)) == NULL) {
        return (-1);
    }
    if (!should_call_stat(options)) {
        return (0);
    }
    if (w_stat(file->name, &file->stat) == -1) {
        free((void*)file->name);
        return (-1);
    }
    return (0);
}

static int
create_file(const struct dirent* entry, t_dlist** list, const t_options* options) {
    t_file*  file = NULL;
    t_dlist* elem = NULL;
    if ((file = malloc(sizeof(*file))) == NULL) {
        goto err;
    }
    if (populate_file(entry, file, options) == -1) {
        goto err_file;
    }
    if ((elem = ft_dlstnew(file)) == NULL) {
        goto err_elem;
    }
    ft_dlstadd_back(list, elem);
    return (0);
err_elem:
    free((void*)file->name);
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
process_file_list(const char* path, t_dlist* list, const t_options* options) {
    t_file* file = NULL;

    if (options->reverse) {
        list = ft_dlstlast(list);
    }
    while (list != NULL) {
        file = list->content;
        if (options->recursive && file->type == DT_DIR) {
            if (ft_strcmp(file->name, ".") == 0 || ft_strcmp(file->name, "..") == 0) {
                goto advance;
            }
            char* pathConcat = malloc(ft_strlen(path) + ft_strlen(file->name) + 2);

            pathConcat[0] = 0;
            ft_strcat(pathConcat, path);
            ft_strcat(pathConcat, "/");
            ft_strcat(pathConcat, file->name);

            printf("%s\n\n", pathConcat);

            file_walk(pathConcat, options);
        }

        printf("%s ", file->name);

    advance:
        if (options->reverse) {
            list = list->prev;
        } else {
            list = list->next;
        }
    }
    printf("\n");
}

int
file_walk(const char* path, const t_options* options) {
    DIR*                 dir       = NULL;
    const struct dirent* dir_entry = NULL;
    t_dlist*             file_list = NULL;

    if ((dir = w_opendir(path)) == NULL) {
        return (-1);
    }
    while ((dir_entry = w_readdir(dir)) != NULL) {
        create_file(dir_entry, &file_list, options);
    }
    sort_file_list(&file_list, options);
    process_file_list(path, file_list, options);

    ft_dlstclear(&file_list, free_file_list);

    (void)closedir(dir);
    return (0);
}
