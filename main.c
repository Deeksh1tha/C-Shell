#include "headers.h"

int main()
{
    // Keep accepting commands
    // getcwd();
    dir_path status;
    getcwd(status.home_dir, sizeof(status.home_dir));
    getcwd(status.cur_dir, sizeof(status.cur_dir));
    status.pre_dir == NULL;
    char commandfile[1024];
    strcpy(commandfile, status.cur_dir);
    CircularQueue *q = malloc(sizeof(CircularQueue));
    initializeQueue(q);
    strcat(commandfile, "/his.bin");
    loadQueueFromFile(q, "his.bin");
    while (1)
    {
        char diff = 0;
        prompt(status);
        char input[4096];
        fgets(input, 4096, stdin);
        char inputCopy[sizeof(input)];
        strcpy(inputCopy, input);
        char *t_ptr;
        const char Delimiter[] = ";&";
        char *token = __strtok_r(inputCopy, Delimiter, &t_ptr);
        while (token != NULL)
        {
            const char delimiter[] = " /\n";
            char temp[1024];
            strcpy(temp, token);
            char *sub_token = strtok(temp, delimiter); // Get the first token
            if (strcmp(sub_token, "warp") == 0)
            {
                warp(&status, sub_token, delimiter);
            }
            else if (strcmp(sub_token, "peek") == 0)
            {
                peek(&status, sub_token, delimiter);
            }
            else if (strcmp(sub_token, "pastevents") == 0)
            {
                pastevents(&status, sub_token, delimiter, q);
            }
            else if (strcmp(sub_token, "proclore") == 0)
            {
                // give_data_process(sub_token, delimiter, getpid());
                proclore(getpid());
            }
            else if (strcmp(sub_token, "\n") != 0)
            {
                pid_t pid = fork();
                if (pid == 0)
                {
                    char *program = strdup(sub_token); // Program to execute
                    char *args[] = {program, "5", NULL};
                    char *ptr;
                    args[0] = strdup(program);
                    int n = 1;
                    sub_token = strtok(NULL, delimiter);
                    while (sub_token != NULL)
                    {
                        args[n++] = sub_token;
                        sub_token = strtok(NULL, delimiter);
                    }
                    args[n] = NULL;
                    execvp(program, args); // Execute the program
                    perror("execvp");
                }
                else if (pid > 0)
                {
                    // This is the parent process
                    wait(NULL); // Wait for the child process to finish
                }
                else
                {
                    perror("fork");
                }
            }
            if (strcmp(sub_token, "pastevents") != 0)
            {
                if (!isEmpty(q))
                {
                    if (strcmp(q->items[q->rear], input) != 0)
                    {
                        enqueue(q, input);
                    }
                }
                else
                {
                    enqueue(q, input);
                }
                saveQueueToFile(q, commandfile);
            }
            if (strchr(input, ';') == NULL && strchr(input, '&') == NULL)
                break;
            token = __strtok_r(NULL, Delimiter, &t_ptr);
        }
    }
}
