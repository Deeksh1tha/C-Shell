#include<stdio.h>
#include<string.h>
#include<stdbool.h>
#include"headers.h"

void initializeQueue(CircularQueue *queue) {
    queue->front = -1;
    queue->rear = -1;
    queue->no_of_elems=0;
}

bool isFull(CircularQueue *queue) {
    return (queue->front == 0 && queue->rear == MAX_SIZE - 1) ||
           (queue->rear == (queue->front - 1 + MAX_SIZE) % MAX_SIZE);
}

bool isEmpty(CircularQueue *queue) {
    return queue->front == -1;
}

void enqueue(CircularQueue *queue, const char *item) {
    if (isFull(queue)) {
       dequeue(queue);
    }

    if (queue->front == -1)
        queue->front = queue->rear = 0;
    else
        queue->rear = (queue->rear + 1) % MAX_SIZE;

    strcpy(queue->items[queue->rear], item);
    // queue->items[queue->rear]=strdup(item);
    queue->no_of_elems++;
    // printf("Enqueued: %s\n", item);
}

const char *dequeue(CircularQueue *queue) {
    // static char emptyString[STRING_LENGTH] = "";

    // if (isEmpty(queue)) {
    //     printf("Queue is empty. Cannot dequeue.\n");
    //     return emptyString;
    // }
    const char *dequeuedItem = queue->items[queue->front];
    if (queue->front == queue->rear)
        queue->front = queue->rear = -1;
    else
        queue->front = (queue->front + 1) % MAX_SIZE;
        queue->no_of_elems--;
    return dequeuedItem;
}
void printQueue(CircularQueue *queue) {
    if (isEmpty(queue)) {
        // printf("Queue is empty.\n");
        return;
    }

    int current = queue->front;
    while (current != queue->rear) {
        printf("%s", queue->items[current]);
        current = (current + 1) % MAX_SIZE;
    }
    printf("%s", queue->items[current]); // Print the last element
}

char saveQueueToFile(CircularQueue* queue, const char* filename) {
    FILE* file = fopen(filename, "wb");
    if (file == NULL) {
        printf("Unable to open file for writing.\n");
        return 0;
    }

    fwrite(queue, sizeof(CircularQueue), 1, file);

    fclose(file);
    return 1;
}

char loadQueueFromFile(CircularQueue* queue, const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        printf("Unable to open file for reading.\n");
        return 0;
    }

    fread(queue, sizeof(CircularQueue), 1, file);

    fclose(file);
    return 1;
}