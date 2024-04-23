//
// Created by plouvel on 23/04/24.
//

#ifndef WRAPPER_H
#define WRAPPER_H

#include <dirent.h>

DIR           *w_opendir(const char *name);
struct dirent *w_readdir(DIR *dirp);
int            w_stat(const char *path, struct stat *buf);
void          *w_malloc(size_t size);

#endif  // WRAPPER_H
