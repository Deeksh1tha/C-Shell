#include"headers.h"
void proclore(int pid){
    pid = (pid == 0)? getpid(): pid;
    char path[512];
    sprintf(path, "/proc/%d/status", pid);
    FILE *status_1 = fopen(path, "r");
    char lines[2000],status;
    int ppid,vmsize;
    while (fgets(lines, sizeof(lines), status_1))
    {
        if(!strncmp(lines, "PPid:", 4)){
            sscanf(lines+4, "%d", &ppid); 
        }
        else if(!strncmp(lines, "VmSize:", 7)){
            sscanf(lines+7, "%d", &vmsize);
        }
        else if(!strncmp(lines, "State:", 6)){
            sscanf(lines+7, "%c", &status);
        }
    }
    char spath_1[200];
    char exec[200];
    sprintf(spath_1, "/proc/%d/exe", pid);
    readlink(spath_1, exec, sizeof(exec)-1);

    printf("Pid : %d\n", pid);
    printf("Process status : %c\n", status);
    printf("Process Group : %d\n", getpgid(pid));
    printf("Virtual Memory : %d\n", vmsize);
    printf("executable Path : %s\n", exec);
}