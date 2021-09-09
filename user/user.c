#define _GNU_SOURCE
#include <stdio.h>

#ifndef VERSION
#define VERSION 51
#endif

int base_version();
extern int base_global_value;

int version()
{
    return VERSION;
}

int global_value = VERSION;

char * fullname()
{
    char * str;
    int ret = asprintf(&str, "my_glob='%d', my_version=%d, base_glob='%d', base_version=%d",
        global_value, version(), base_global_value, base_version()
    );

    if (ret == -1)
        return NULL;

    return str;
}
