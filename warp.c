#include "headers.h"

void warp(dir_path* status,char* token,const char* delimiter)
{
    token = strtok(NULL, delimiter);
    do
    {
        const char *new_dir = token;
        if (new_dir == NULL || strcmp(new_dir, "~") == 0)
            chdir(status->home_dir);
        else if(strcmp(new_dir,"-")==0)
        {
            if(status->pre_dir==NULL)
            {
                perror(status->pre_dir);
            }
            else
            chdir(status->pre_dir);
        }
        else
        {
            if (chdir(new_dir) != 0)
            {
                perror("chdir");
                // return 1;
            }
        }
        token = strtok(NULL, delimiter);
    } while (token != NULL);
        strcpy(status->pre_dir,status->cur_dir);
    if (getcwd(status->cur_dir, sizeof(status->cur_dir)) != NULL)
    {
        printf("%s\n", status->cur_dir);
    }
    else
    {
        perror("getcwd");
        // return 1;
    }
    return;       
}