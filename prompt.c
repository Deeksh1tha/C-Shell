#include "headers.h"

void prompt(dir_path status) {
    // Do not hardcode the prmopt
    uid_t user_id = getuid(); // Get the user ID of the current user

    struct passwd *pw = getpwuid(user_id); // Get user information
    if (pw == NULL) {
        perror("getpwuid");
    }

    printf("\x1b[32m""<%s@", pw->pw_name);
    char hostname[128];
    gethostname(hostname,sizeof(hostname));
    printf("%s""\x1b[0m"":",hostname);
    int l1=strlen(status.home_dir);
    int l2=strlen(status.cur_dir);
    // printf("%s\n",status.home_dir);
    // printf("%s\n",status.cur_dir);
    if(l2-l1!=0)
    {
        if(strncmp(status.cur_dir,status.home_dir,strlen(status.home_dir))!=0)
        {
            printf("\x1b[34m""%s""\x1b[0m"">",status.cur_dir);
        }
        else
        printf("\x1b[34m""%s""\x1b[0m"">",&status.cur_dir[l1]);
    }
    else
    printf("\x1b[34m""~>""\x1b[0m");
    return;
    // printf("<Everything is a file> ");    
}
