#ifndef GENERIC_QUEUE_H
#define GENERIC_QUEUE_H

typedef struct Node {
    void* data;
    struct Node* next;
} Node;

typedef struct Queue {
    struct Node* rear;
    struct Node* front;
    unsigned    dataSize;
} Queue;

Queue* Q_initiate(unsigned dataSize);
void  Q_destroy(Queue* q);
int   Q_enqueue(Queue* q, const void* input);
int   Q_dequeue(Queue* q);
void* Q_rear(const Queue* q);
void* Q_front(const Queue* q);
int   Q_iterate(const Queue* q, void (*print)(void*));

#include "generic_queue.c"

#endif