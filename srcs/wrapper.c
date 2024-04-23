//
// Created by plouvel on 23/04/24.
//

#include <dirent.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/stat.h>

#include "libft.h"

DIR *
w_opendir(const char *name) {
    DIR *dir = NULL;

    dir = opendir(name);
    if (dir == NULL) {
        ft_error(0, errno, "opendir");
    }
    return dir;
}

struct dirent *
w_readdir(DIR *dir) {
    struct dirent *entry = NULL;

    errno = 0;
    entry = readdir(dir);
    if (entry == NULL && errno != 0) {
        ft_error(0, errno, "readdir");
    }
    return entry;
}

int
w_stat(const char *path, struct stat *buf) {
    int ret = 0;

    ret = stat(path, buf);
    if (ret == -1) {
        ft_error(0, errno, "stat");
    }
    return ret;
}

void *
w_malloc(size_t size) {
    void *ptr = NULL;

    ptr = malloc(size);
    if (ptr == NULL) {
        ft_error(0, errno, "malloc");
    }

    return ptr;
}
