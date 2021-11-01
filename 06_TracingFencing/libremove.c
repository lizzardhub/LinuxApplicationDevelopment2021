#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <dlfcn.h>

typedef int (*orig_remove_f_type)(const char *pathname);

int
remove(const char *pathname) {
    if (strstr(pathname, "PROTECT")) {
        printf("Protected %s\n", pathname);
        return 0;
    }

    orig_remove_f_type orig_remove;
    orig_remove = (orig_remove_f_type)dlsym(RTLD_NEXT, "remove");
    return orig_remove(pathname);
}