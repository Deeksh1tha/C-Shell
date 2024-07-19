#include "headers.h"
void pastevents(dir_path* status, char *token, const char *delimiter, CircularQueue *q)
{
    // while (token!=NULL)
    // {
    token = strtok(NULL, delimiter);
    if (token != NULL)
    {
        if (strcmp(token, "execute") == 0)
        {
            token = strtok(NULL, delimiter);
            if (token != NULL)
            {
                int x=atoi(token);
                enqueue(q,q->items[q->front+(x-1)]);
                char temp[1024];
                strcpy(temp,q->items[q->front+(x-1)]);
                token=strtok(temp,delimiter);
                if (strcmp(token, "warp") == 0)
                {
                    warp(status, token, delimiter);
                }
                else if (strcmp(token, "peek") == 0)
                {
                    peek(status, token, delimiter);
                }
                else if (strcmp(token, "pastevents") == 0)
                {
                    pastevents(status, token, delimiter, q);
                }
            }
        }
        if(strcmp(token,"purge")==0)
        {
            FILE* fp=fopen("his.bin","w");
            fclose(fp);
            initializeQueue(q);
        }
    }
    else
    {
        printQueue(q);
    }
}