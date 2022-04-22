#include <stdlib.h>
#include <string.h>
#include "generic_queue.h"

Queue* Q_initiate(unsigned dataSize) {
    Queue* q = malloc(sizeof(Queue));
    if (q) {
        q->front = NULL;
        q->rear = NULL;
        q->dataSize = dataSize;
    }
    return q;
}

void Q_destroy(Queue* q) {
    Node* current = q->front, * next = NULL;
    while (current) {
        next = current->next;
        free(current->data);
        free(current);
        current = next;
    }
    free(q);
}

void* Q_rear(const Queue* q) {
    return q->rear ? q->rear->data : NULL;
}

void* Q_front(const Queue* q) {
    return q->front ? q->front->data : NULL;
}

int Q_enqueue(Queue* q, const void* input) {
    Node* newNode = malloc(sizeof(Node));
    if (newNode) {
        newNode->data = malloc(sizeof(q->dataSize));
        if (newNode->data) {
            memcpy(newNode->data, input, q->dataSize);
            if (q->front) {
                q->rear->next = newNode;
                q->rear = newNode;
            }
            else {
                q->front = newNode;
                q->rear = newNode;
            }
            q->rear->next = NULL;
            return EXIT_SUCCESS;
        }
        else {
            free(newNode);
        }
    }
    return EXIT_FAILURE;
}

int Q_dequeue(Queue* q) {
    Node* temp = NULL;
    if (q->front) {
        temp = q->front;
        if (temp->next) {
            q->front = q->front->next;
        }
        else {
            q->front = NULL;
            q->rear = NULL;
        }
        free(temp->data);
        free(temp);
        return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;
}

int Q_iterate(const Queue* q, void (*print)(void*)) {
    if (q->front) {
        Node* node = q->front;
        while (node) {
            print(node->data);
            node = node->next;
        }
        return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;
}