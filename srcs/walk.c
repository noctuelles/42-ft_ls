
#include "walk.h"

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#include "ft_ls.h"
#include "libft.h"
#include "mem.h"
#include "sort.h"
#include "utils.h"
#include "wrapper.h"

typedef int (*sort_fn)(const void*, const void*);

static int
populate_file(t_file* file, const struct dirent* entry,
              const t_options* options) {
    file->type = entry->d_type;
    ft_strlcpy(file->name, entry->d_name, NAME_MAX);
    if (!should_call_stat(options)) {
        return (0);
    }
    if (w_stat(file->name, &file->stat) == -1) {
        return (-1);
    }
    return (0);
}

static sort_fn
get_sorting_fn(const t_options* options) {
    int (*sort_fn)(const void*, const void*) = NULL;

    if (options->sort_by_time) {
        sort_fn = sort_by_time;
    } else {
        sort_fn = sort_by_file_name;
    }

    return sort_fn;
}

static int
crawl_files(DIR* dir, t_vector* files_vector, const t_options* options) {
    struct dirent* entry = NULL;
    t_file         file  = {0};

    while ((entry = readdir(dir)) != NULL) {
        if (!options->all && entry->d_name[0] == '.') {
            continue;
        }
        if (populate_file(&file, entry, options) == -1) {
            return (-1);
        }
        if (vector_push_back(files_vector, &file) == NULL) {
            return (-1);
        }
    }
    return (0);
}

static void
init_iter(const t_vector* files_vector, size_t* i, ssize_t* step,
          bool reverse) {
    if (reverse) {
        *i    = vector_size(files_vector);
        *step = -1;
    } else {
        *i    = 1;
        *step = 1;
    }
}

static const char*
build_path(const char* old_path, const char* dir) {
    char*  new_path      = NULL;
    size_t old_path_size = 0;

    new_path = malloc((ft_strlen(old_path) + 1 + ft_strlen(dir) + 1) *
                      sizeof(*new_path));
    if (new_path == NULL) {
        return (NULL);
    }
    old_path_size = ft_strlen(old_path);
    *new_path     = '\0';
    ft_strcat(new_path, old_path);
    if (old_path[old_path_size - 1] != '/') {
        ft_strcat(new_path, "/");
    }
    ft_strcat(new_path, dir);

    return (new_path);
}

static int
iter_recursive(const char* path, const t_vector* files_vector,
               const t_options* options) {
    size_t        i        = 0;
    ssize_t       step     = 1;
    const t_file* files    = NULL;
    const char*   new_path = NULL;

    init_iter(files_vector, &i, &step, options->reverse);
    files = vector_data(files_vector);
    while (i > 0 && i <= vector_size(files_vector)) {
        if (files[i - 1].type == DT_DIR &&
            ft_strcmp(files[i - 1].name, ".") != 0 &&
            ft_strcmp(files[i - 1].name, "..") != 0) {
            new_path = build_path(path, files[i - 1].name);
            if (file_walk(new_path, options) == -1) {
                free((void*)new_path);
                return (-1);
            }
            free((void*)new_path);
        }

        i += step;
    }
    return (0);
}

static int
iter_files(const char* path, const t_vector* files_vector,
           const t_options* options) {
    size_t        i     = 0;
    ssize_t       step  = 1;
    const t_file* files = NULL;

    init_iter(files_vector, &i, &step, options->reverse);
    files = vector_data(files_vector);
    while (i > 0 && i <= vector_size(files_vector)) {
        printf("%s ", files[i - 1].name);
        i += step;
    }
    printf("\n");
    if (options->recursive) {
        iter_recursive(path, files_vector, options);
    }
    return (0);
}

int
file_walk(const char* path, const t_options* options) {
    DIR*      dir   = NULL;
    t_vector* files = NULL;
    int       ret   = -1;

    if ((files = vector_new(20, sizeof(t_file))) == NULL) {
        goto ret;
    }
    if ((dir = w_opendir(path)) == NULL) {
        goto clean_files;
    }
    ret = crawl_files(dir, files, options);
    (void)closedir(dir);
    if (ret == 0) {
        vector_sort(files, get_sorting_fn(options));
        if (options->recursive) {
            printf("%s:\n\n", path);
        }
        ret = iter_files(path, files, options);
    }
clean_files:
    vector_free(&files);
ret:
    return (ret);
}
