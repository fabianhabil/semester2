#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_QUEUE 10

// 2501976503 - Fabian Habi Ramdhan

int queue[MAX_QUEUE];
int rear = -1, front = -1;

void enterToContinue() {
    printf("Tekan Enter untuk melanjutkan!");
    getchar();
}

int isFull() {
    return rear == MAX_QUEUE - 1;
}

int isEmpty() {
    return front > rear || front == -1;
}

void pop() {
    if (isEmpty()) {
        printf("Queue underflow\n");
    }
    else {
        int val = queue[front];
        front++;
        printf("%d dihapus!\n", val);
        enterToContinue();
    }
}

void enqueue(int num) {
    if (isFull()) {
        printf("Queue overflow!\n");
    }
    else {
        if (front == -1 && rear == -1) {
            front = rear = 0;
        }
        else {
            rear++;

        }
        queue[rear] = num;
    }
}

void display() {
    if (isEmpty()) {
        printf("Masih kosong!\n");
    }
    else {
        printf("Ada %d Antrian!\n", (rear - front) + 1);
        for (int i = front; i <= rear; i++) {
            printf("Antrian ke %d = %d\n", i + 1, queue[i]);
        }
    }
}

int main() {
    display();
    enqueue(5);
    enqueue(2);
    enqueue(3);
    enqueue(10);
    enqueue(9);
    // enqueue(12);
    // enqueue(13);
    // enqueue(2);
    pop();
    pop();
    pop();
    pop();
    pop();
    pop();

    enqueue(7);
    enqueue(10);
    enqueue(12);

    // enqueue(1);


    display();
}