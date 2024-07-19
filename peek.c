#include "headers.h"

int compare(const void *a, const void *b)
{
    char temp_a[1024];
    char temp_b[1024];
    strcpy(temp_a, *(const char **)a);
    strcpy(temp_b, *(const char **)b);
    int i = 0;
    while (temp_a[i] != '\0')
    {
        temp_a[i] = tolower(temp_a[i]);
        i++;
    }
    i = 0;
    while (temp_b[i] != '\0')
    {
        temp_b[i] = tolower(temp_b[i]);
        i++;
    }
    return strcmp((char *)temp_a, (char *)temp_b);
}
char *get_permissions(__mode_t mode)
{
    static char perms[10];
    strcpy(perms, "---------");

    if (S_ISDIR(mode))
        perms[0] = 'd';
    if (mode & S_IRUSR)
        perms[1] = 'r';
    if (mode & S_IWUSR)
        perms[2] = 'w';
    if (mode & S_IXUSR)
        perms[3] = 'x';
    if (mode & S_IRGRP)
        perms[4] = 'r';
    if (mode & S_IWGRP)
        perms[5] = 'w';
    if (mode & S_IXGRP)
        perms[6] = 'x';
    if (mode & S_IROTH)
        perms[7] = 'r';
    if (mode & S_IWOTH)
        perms[8] = 'w';
    if (mode & S_IXOTH)
        perms[9] = 'x';

    return perms;
}
void peek(dir_path* status, char *token, const char *delimiter)
{
    int a_flag = 0;
    int l_flag = 0;
    while (token != NULL)
    {
        token = strtok(NULL, delimiter);
        if (token != NULL)
        {
            if (strcmp(token, "-l") == 0)
            {
                l_flag = 1;
            }
            else if (strcmp(token, "-a") == 0)
            {
                a_flag = 1;
            }
            else if (strcmp(token, "-la") == 0 || strcmp(token, "-al") == 0)
            {
                l_flag = 1;
                a_flag = 1;
            }
            else
            {
                char path[1024];
                if (strcmp(token, "~") == 0)
                {
                    strcpy(path, status->home_dir);
                }
                else if (strcmp(token, "-") == 0)
                {
                    strcpy(path, status->pre_dir);
                }
                else
                {
                    strcpy(path, token);
                }
                DIR *dir = opendir(path);
                if (dir == NULL)
                {
                    perror("opendir");
                    return;
                }
                struct dirent *entry;
                int count = 0;
                while ((entry = readdir(dir)) != NULL)
                {
                    count++;
                }
                // Allocate memory for the file names
                char **file_names = (char **)malloc(count * sizeof(char *));
                for (int i = 0; i < count; i++)
                {
                    file_names[i] = (char *)malloc(4096);
                }
                // Reset directory stream and populate file_names
                rewinddir(dir);
                int i = 0;
                while ((entry = readdir(dir)) != NULL)
                {
                    strcpy(file_names[i], entry->d_name);
                    i++;
                }
                qsort(file_names, count, sizeof(char *), compare);
                if (l_flag == 1 && a_flag == 1)
                {
                    for (int i = 0; i < count; i++)
                    {
                        char fullpath[4096];
                        snprintf(fullpath, sizeof(fullpath), "%s/%s", path, file_names[i]);
                        struct stat file_info;
                        if (stat(fullpath, &file_info) == 0)
                        {
                            struct passwd *pw = getpwuid(file_info.st_uid);
                            struct group *gr = getgrgid(file_info.st_gid);
                            char permissions[10];
                            strftime(permissions, sizeof(permissions), "%b %d %H:%M", localtime(&file_info.st_mtime));
                            printf("%s %2ld %s %s %5lld %s ",
                                   get_permissions(file_info.st_mode),
                                   file_info.st_nlink,
                                   pw->pw_name,
                                   gr->gr_name,
                                   (long long)file_info.st_size,
                                   permissions);
                            if (S_ISREG(file_info.st_mode))
                            {
                                if (file_info.st_mode & S_IXUSR)
                                {
                                    printf(green "%s\n" white, file_names[i]);
                                }
                                else
                                {
                                    printf("%s\n", file_names[i]);
                                }
                            }
                            else if (S_ISDIR(file_info.st_mode))
                            {
                                printf(blue "%s\n" white, file_names[i]);
                            }
                        }
                    }
                }
                else if (l_flag == 0 && a_flag == 1)
                {
                    for (int i = 0; i < count; i++)
                    {
                        char fullpath[4096];
                        snprintf(fullpath, sizeof(fullpath), "%s/%s", path, file_names[i]);
                        struct stat file_info;
                        if (stat(fullpath, &file_info) == 0)
                        {
                            if (S_ISREG(file_info.st_mode))
                            {
                                if (file_info.st_mode & S_IXUSR)
                                {
                                    printf(green "%s\n" white, file_names[i]);
                                }
                                else
                                {
                                    printf("%s\n", file_names[i]);
                                }
                            }
                            else if (S_ISDIR(file_info.st_mode))
                            {
                                printf(blue "%s\n" white, file_names[i]);
                            }
                        }
                    }
                }
                else
                {
                    for (int i = 0; i < count; i++)
                    {
                        char fullpath[4096];
                        if (file_names[i][0] != '.')
                        {
                            snprintf(fullpath, sizeof(fullpath),"%s/%s",path,file_names[i]);
                            struct stat file_info;
                            if (stat(fullpath, &file_info) == 0)
                            {
                                struct passwd *pw = getpwuid(file_info.st_uid);
                                struct group *gr = getgrgid(file_info.st_gid);
                                char permissions[10];
                                strftime(permissions, sizeof(permissions), "%b %d %H:%M", localtime(&file_info.st_mtime));

                                if (file_names[i][0] != '.')
                                {
                                    printf("%s %2ld %s %s %5lld %s ",
                                           get_permissions(file_info.st_mode),
                                           file_info.st_nlink,
                                           pw->pw_name,
                                           gr->gr_name,
                                           (long long)file_info.st_size,
                                           permissions);
                                    if (S_ISREG(file_info.st_mode))
                                    {
                                        if (file_info.st_mode & S_IXUSR)
                                        {
                                            printf(green "%s\n" white, file_names[i]);
                                        }
                                        else
                                        {
                                            printf("%s\n", file_names[i]);
                                        }
                                    }
                                    else if (S_ISDIR(file_info.st_mode))
                                    {
                                        printf(blue "%s\n" white, file_names[i]);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
