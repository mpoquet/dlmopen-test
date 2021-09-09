#define _GNU_SOURCE
#include <dlfcn.h>
#include <stdlib.h>
#include <stdio.h>

#ifndef VERSION
#define VERSION 37
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

struct User
{
    void * handle;
    int (*version)(void);
    int* global_value;
    char* (*fullname)(void);
    int (*base_version)(void);
    int* base_global_value;
};

void * load_symbol(void * handle, const char * symbol)
{
    void * address = dlsym(handle, symbol);
    if (address == NULL)
    {
        printf("dlsym failed: %s'\n", dlerror());
    }
    return address;
}

int populate_user(const char * lib_path, struct User * user)
{
    user->handle = dlmopen(LM_ID_NEWLM, lib_path, RTLD_NOW | RTLD_LOCAL | RTLD_DEEPBIND);
    //user->handle = dlopen(lib_path, RTLD_NOW | RTLD_LOCAL | RTLD_DEEPBIND);
    if (user->handle == NULL)
    {
        printf("dlmopen error: %s'\n", dlerror());
        return 0;
    }

    user->version = load_symbol(user->handle, "version");
    user->global_value = load_symbol(user->handle, "global_value");
    user->fullname = load_symbol(user->handle, "fullname");
    user->base_version = load_symbol(user->handle, "base_version");
    user->base_global_value = load_symbol(user->handle, "base_global_value");

    return !(user->version == NULL ||
             user->global_value == NULL ||
             user->fullname == NULL ||
             user->base_version == NULL ||
             user->base_global_value == NULL);
}

int main(int argc, char ** argv)
{
    char * str = fullname();
    printf("runner fullname: %s\n", str);
    free(str);

    // Load all user libs
    const int nb_users = argc-1;
    struct User users[nb_users];
    for (int i = 1; i < argc; ++i)
    {
        if (!populate_user(argv[i], &users[i-1]))
        {
            printf("could not populate user %d, aborting.\n", i);
            abort();
        }
    }

    printf("All users have been loaded.\n");
    str = fullname();
    printf("runner fullname: %s\n", str);
    free(str);

    for (int i = 0; i < nb_users; ++i)
    {
        char * value = users[i].fullname();
        printf("user %d fullname: %s\n", i, value);
        free(value);
    }

    printf("Changing global values.\n");
    global_value = 42;
    base_global_value = 420;
    for (int i = 0; i < nb_users; ++i)
    {
        *(users[i].global_value) = (i+1)*10;
        *(users[i].base_global_value) = (i+1)*100;
    }

    printf("Printing fullnames again.\n");
    str = fullname();
    printf("runner fullname: %s\n", str);
    free(str);
    for (int i = 0; i < nb_users; ++i)
    {
        char * value = users[i].fullname();
        printf("user %d fullname: %s\n", i, value);
        free(value);
    }

    printf("Removing user libs from memory.\n");
    for (int i = 0; i < nb_users; ++i)
    {
        if (dlclose(users[i].handle) != 0)
        {
            printf("could not dlclose user %d: %s", i, dlerror());
        }
    }

    str = fullname();
    printf("runner fullname: %s\n", str);
    free(str);

    return 0;
}
