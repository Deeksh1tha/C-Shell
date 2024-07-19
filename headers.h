#ifndef HEADERS_H_
#define HEADERS_H_

// #include <stdio.h>
#include <stdio.h>
#include <pwd.h>
#include <limits.h>
#include <unistd.h>
#include<sys/stat.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include<dirent.h>
#include <errno.h>
#include <getopt.h>
#include <grp.h>
#include<time.h>
#include<stdbool.h>
#include<sys/wait.h>
#include "structs.h"
#define  green "\x1b[32m"
#define  blue "\x1b[34m"
#define white "\x1b[0m"

// #include "prompt.h"
void prompt(dir_path status);
void warp(dir_path* status,char* token,const char* delimiter);
int compare(const void *a, const void *b);
void peek(dir_path* status,char* token,const char* delimiter);
void initializeQueue(CircularQueue *queue);
bool isFull(CircularQueue *queue) ;
bool isEmpty(CircularQueue *queue);
void enqueue(CircularQueue *queue, const char *item);
const char *dequeue(CircularQueue *queue);
void pastevents(dir_path* status, char *token, const char *delimiter,CircularQueue* q);
char saveQueueToFile(CircularQueue* queue, const char* filename);
char loadQueueFromFile(CircularQueue* queue, const char* filename);
void printQueue(CircularQueue *queue);
char *get_permissions(__mode_t mode);
// void give_data_process(char* token,const char* delimiter,int process_id);
void proclore(int pid);
// #include "warp.h"


#endif